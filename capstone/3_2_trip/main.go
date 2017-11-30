package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"

	"github.com/aws/aws-sdk-go/aws"
	"github.com/aws/aws-sdk-go/aws/credentials"
	"github.com/aws/aws-sdk-go/aws/session"
	"github.com/guregu/dynamo"
)

const workers = 80

func main() {
	db := dynamo.New(session.New(), &aws.Config{
		Region:      aws.String("us-east-1"),
		Credentials: credentials.NewEnvCredentials(),
	})
	table := db.Table("trips")

	file, err := os.Open("./results/part-00000")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	c := make(chan flight, workers)

	for i := 0; i != workers; i++ {
		go func() {
			for t := range c {
				err := table.Put(t).Run()
				if err != nil {
					fmt.Println(err)
				}
			}
		}()
	}

	// put item
	scanner := bufio.NewScanner(file)
	i := 0
	for scanner.Scan() {
		i++
		parts := strings.Split(scanner.Text(), ",")
		hour, _ := strconv.ParseInt(parts[6], 10, 64)
		delay, _ := strconv.ParseFloat(strings.Trim(parts[7], " \t\r\n"), 64)
		f := flight{
			Id:           fmt.Sprintf("%s_%s_%s_%s",parts[0],parts[5],parts[1],parts[2]),
			AmPm:         parts[0],
			FlightNumber: parts[4],
			Origin:       parts[1],
			Dest:         parts[2],
			Carrier:      parts[3],
			Day:          parts[5],
			Hour:         hour,
			Delay:        delay,
		}
		c <- f
		if i%100 == 0 {
			log.Println(i)
		}
	}
	close(c)
}

type flight struct {
	Id           string
	AmPm         string
	FlightNumber string
	Origin       string
	Dest         string
	Carrier      string
	Day          string
	Hour         int64
	Delay        float64
}
