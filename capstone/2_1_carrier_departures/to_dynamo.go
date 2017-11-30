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

const workers = 3

func main() {
	db := dynamo.New(session.New(), &aws.Config{
		Region:      aws.String("us-east-1"),
		Credentials: credentials.NewEnvCredentials(),
	})
	table := db.Table("carrier-departures")

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
	for scanner.Scan() {
		parts := strings.Split(scanner.Text(), " ")
		delay, _ := strconv.ParseFloat(strings.Trim(parts[1], " \t\r\n"), 64)
		f := flight{
			Id:    parts[0],
			Delay: delay,
		}
		c <- f
	}
	close(c)
}

type flight struct {
	Id    string
	Delay float64
}
