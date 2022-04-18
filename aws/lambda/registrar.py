import json
import boto3

dynamodb = boto3.resource('dynamodb')


def lambda_handler(event, context):
    table = dynamodb.Table('Usuarios')
    
    existe = table.get_item(TableName='Usuarios', Key={'user': event['user']})
    
    try:
        a = existe['Item']
        response = False
    except:
        response = True
        event['Intentos'] = 0
        table.put_item(Item=event)
        
    return {
        'statusCode': 200,
        'body': response
    }

