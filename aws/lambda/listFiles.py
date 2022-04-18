import json
import boto3

s3 = boto3.resource("s3")

def lambda_handler(event, context):
    
    bucket_name = "elbucketbananero"
    dir_name = event["dirname"]
    
    bucket = s3.Bucket(bucket_name)
    
    response = bucket.objects.filter(Delimiter="/",Prefix=dir_name + "/")
    
    print("--------------")
    listaFicheros = list()
    for objeto in response:
        if objeto.key.endswith(".mp4"):
            listaFicheros.append(objeto.key)
    print("--------------")
    
    return{
        'statusCode': 200,
        'body': json.dumps(listaFicheros)
    } 


