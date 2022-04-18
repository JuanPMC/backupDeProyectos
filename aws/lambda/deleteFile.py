import json
import boto3

s3 = boto3.client("s3")

def lambda_handler(event, context):
    
    bucket_name = "elbucketbananero"
    file_name = event["filename"]
    
    response = s3.delete_object(Bucket=bucket_name,Key=file_name)
    
    
    return {
        'statusCode': 200,
        'body': json.dumps(response)
    }

