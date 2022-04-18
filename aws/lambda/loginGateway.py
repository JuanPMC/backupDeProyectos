import json
import boto3

dynamodb = boto3.resource('dynamodb')

def loginUser(user,password):
    respuesta = False
    
    table = dynamodb.Table('Usuarios')
    try:
        response = table.get_item(TableName='Usuarios', Key={'user': user})
        item = response['Item']
    
        if item['pass'] == password and (item['Intentos'] =< 3):
            respuesta = True
            item['Intentos'] = 0
        else:
            item['Intentos'] += 1 

        table.put_item(Item=item)
    except:
        pass
    return respuesta

def htmlCreator(texto):
    bucket_name = 'elbucketbananero'
    
    msg = """<!DOCTYPE html>
<html>
<head>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script>
var username = "lavainatolocabananeraesaahiYHYFDGG";

function personalizarDashboard(){
	document.getElementById("perfil").innerHTML = "<h1> Perfile de " + username +  ": </h1>";
}

function aniadirFicheroALista(fichero){
	let borrar = '<a href="http://54.166.39.218:30159/delete_gateway.php?filename=' + fichero + '">[Borrar]<a>'
	let verVid = '<a href="/verVideo.html?video=' + fichero + '">[Ver]<a>'
	document.getElementById("ficheros").innerHTML += "<li> "+ fichero +" " + borrar + " " +  verVid +"</li>";
}

function getFicheros() {
	var asd=$.get(
 			"http://54.166.39.218:30159/listFiles.php?dirname=" + username,
		    {},
		    function(data) {

		       var json=JSON.parse(data);
                       json=JSON.parse(json);

		       json.forEach(aniadirFicheroALista);
		    }
		)
  
}

function getAWSKeys() {
	var asd=$.get(
 			"http://54.166.39.218:30159/keys_gateway.php",
		    {},
		    function(data) {

		       var json=JSON.parse(data);
                       json=JSON.parse(json);
		       document.getElementById("Policy").value = json.stringToSign;
		       document.getElementById("X-Amz-Credential").value = json.xAmzCredential;		
		       document.getElementById("X-Amz-Date").value = json.amzDate;		
		       document.getElementById("X-Amz-Signature").value = json.stringSigned;	
		       document.getElementById("X-Amz-Security-Token").value = json.securityToken;	
			
		    }
		)
  
}

function creation(){
	getAWSKeys();
	personalizarDashboard();
	getFicheros();
}

function setKeyFilename() {
	document.getElementById("key").value = username + "/" + document.getElementById("file").value.substring(document.getElementById("file").value.lastIndexOf('\\\\')+1);	
}

function array2Url(a){
  let outPlace = ''
  let b = a.split(",");
  b.forEach((elem, index) => {
    outPlace += "&tags[]=" +elem;
  });
  return outPlace;
}

function sendMetadata(){
  titulo = document.getElementById("titulo").value;
  tags = document.getElementById("tags").value;
  localizacion = document.getElementById("key").value;

  console.log("http://54.166.39.218:30159/video_gateway.php?videoTitle=" + titulo + array2Url(tags) + "&localizacion=" + localizacion + "&usuario=" + username);

  var asdMetadata=$.get(
      "http://54.166.39.218:30159/video_gateway.php?videoTitle=" + titulo + array2Url(tags) + "&localizacion=" + localizacion + "&usuario=" + username,
        {},
        function(data){
          document.getElementById("uploadForm").submit();
        }
    )
}

function operaciones(){
  setKeyFilename();
  sendMetadata();
}

</script>



</head>
<body onload="creation()">
<a href="search.html">search</a>
<center>

<div id="perfil"> </div>

<h2>Subir video al perfil:</h2>

<label >titulo</label>
<input type="text"  id="titulo" name="X-Amz-Credential" value="" />
<label >tags</label>
<input type="text"  id="tags" name="X-Amz-Credential" value="" />

<form action="http://elbucketbananero.s3.us-east-1.amazonaws.com/" id="uploadForm" method="post" enctype="multipart/form-data">
  <label >X-Amz-Credential</label>
  <input type="text"  id="X-Amz-Credential" name="X-Amz-Credential" value="" />
  <label >X-Amz-Date</label>
  <input type="text"  id="X-Amz-Date" name="X-Amz-Date" value="" />
  <label >Policy  (b64Policy)</label>
  <input type="text"  id="Policy" name="Policy" value="" />
  <label >X-Amz-Signature</label>
  <input type="text"   id="X-Amz-Signature" name="X-Amz-Signature" value="" />
  
	<input type="input" id="key" name="key" value="fichero.sln" /><br />
    <input type="hidden" name="acl" value="public-read" />
    <input type="hidden" name="success_action_redirect" value="http://elbucketbananero.s3-website-us-east-1.amazonaws.com/success.html" />
    <input type="text"   name="X-Amz-Algorithm" value="AWS4-HMAC-SHA256" />
  	<input type="text" id="X-Amz-Security-Token" name="X-Amz-Security-Token" value=""/>
   Select file to upload:
    <input type="file" name="file" id="file">
</form>
<button onclick="operaciones()" >Upload</button>

<h2>Videos del usuario:</h2>
<ul id="ficheros"></ul>

</center>

</body>
</html>""";
    msg = msg.replace("lavainatolocabananeraesaahiYHYFDGG", texto)

    encoded_string = msg.encode("utf-8")
    file_name = "success.html"
        
    s3 = boto3.resource("s3")
    s3.Bucket(bucket_name).put_object(Key=file_name, Body=encoded_string,ContentType='text/html')
    object_acl = s3.ObjectAcl(bucket_name,file_name)
    object_acl.put(ACL   = 'public-read')

def lambda_handler(event, context):
    user=event["Login"]["user"]
    password=event["Login"]["pass"]
    
    resultado = loginUser(user,password)
    
    if resultado:
        htmlCreator(user)
    
    return {
        'statusCode': 200,
        'body': json.dumps(resultado)
    }

