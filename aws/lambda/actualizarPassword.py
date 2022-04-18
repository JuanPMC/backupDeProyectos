import json
import boto3

dynamodb = boto3.resource('dynamodb')


def lambda_handler(event, context):
    table = dynamodb.Table('Usuarios')
    
    existe = table.get_item(TableName='Usuarios', Key={'user': event['user']})
    
    response = False
    try:
        a = existe['Item']
        if a['frase'] == event['frase'] && a['Intentos'] < 3:
            table.put_item(Item=event)
            response = True
    except:
       pass
        
    return {
        'statusCode': 200,
        'body': response
    }


