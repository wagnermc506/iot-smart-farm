from asyncore import write
from unittest.mock import DEFAULT
from influxdb_client import InfluxDBClient, Point 
from influxdb_client.client.write_api import SYNCHRONOUS

DEFAULTS = {
    "bucket": "smart-farm",
    "host": "http://localhost:8086",
    "org": "farm-inc",
    "token": "qHjIFeu63T4CW3AOAobeLBk6J8583iCqA7eiw49ezZJr1wSVWHtfTcYnaczhqULJbw1uKDFTRABt-rUNNct_YQ=="
}

class InfluxClient:
    client = None
    write_api = None
    query_api = None
    bucket = None

    def __init__(self, host, org, token, bucket):
        self.client = InfluxDBClient(url=host, org=org, token=token)
        self.write_api = self.client.write_api(write_options=SYNCHRONOUS)
        self.query_api = self.client.query_api()
        self.bucket = bucket

    def write(self, measurement_name, tag_key, tag_value, fields):
        p = Point(measurement_name).tag(tag_key, tag_value)
        for i in fields:
            p = p.field(i[0], i[1])
        self.write_api.write(bucket=self.bucket, record=p)

    def get_client(self):
        return self.client


if __name__ == '__main__':
    client = InfluxDBClient(url=DEFAULTS['host'], org=DEFAULTS['org'], token=DEFAULTS['token'])
    query_api = client.query_api()

    tables = query_api.query('from(bucket:"smart-farm") |> range(start: -30d)')

    for table in tables:
        print(table)
        for row in table.records:
                print(row.values)

