./hadoop jar ../share/hadoop/tools/lib/hadoop-streaming-2.8.2.jar -mapper mapper.py -reducer reducer.py -input test_data.csv -output /tmp/top_airports3
