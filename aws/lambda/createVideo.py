import json
import boto3

dynamodb = boto3.resource('dynamodb')


def lambda_handler(event, context):
    table = dynamodb.Table('Videos')
    
    table.put_item(Item=event)
        
    return {
        'statusCode': 200,
        'body': True
    }

