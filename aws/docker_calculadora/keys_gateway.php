

<?php

	$aws_access_key_id='ASIAXMONIVDMIMAWVYGR';

	$aws_secret_access_key='Fk27oB34boVTbG99RoZR8CsbIY99xjSnCvOhmA3y';

	$aws_session_token='FwoGZXIvYXdzEPj//////////wEaDL0qH65jhRmcz2FokyLAASkR++cOOTMrzNIdJcRXW2diKtP3UFgLwWrBNZla1tvVidwqN6PgWw5kokz0VR07U336I8i7F8NaJsjwtMxQvF73g7dkOqkHBIJzgKm1xh++Cocj4zh3VJ0Cnoww988dR0zBIBAASdAWjSGHdqPrrUoJEkEebCffZmlCQpR+l4k+vy5wa//CLEwZcnh4n1+omVP1NB5oFhaPC0wTA6NSKe9zlWws2FIUnTiYtRzFift+Gyt+DVjCfJQ3figLGzC+eiiS+sKNBjItUMjfDRXs1GSlpNfDKV3DmzCb4rpUNzx9DKZi9TF9r9ljzb1kNMu0tf8u6rzo';

	$lambda_func='s3Keys';
	$payload='{"queryStringParameters": {';

	foreach ($_GET as $key => $value) {

		$payload .= '"' . $key . '":"' . $value .'",';

	}

	$payload=substr($payload, 0, -1);

	$payload.='}}';

	$cmd=' AWS_ACCESS_KEY_ID='. $aws_access_key_id .

	     ' AWS_SECRET_ACCESS_KEY='. $aws_secret_access_key .

             ' AWS_SESSION_TOKEN='. $aws_session_token . ' aws lambda invoke --region us-east-1 --function-name '. $lambda_func . ' /tmp/resp.json 2>&1';

	exec( $cmd,$result,$result2);

	header('Access-Control-Allow-Origin: *');

	$result=file_get_contents("/tmp/resp.json");

	$json=json_decode($result,true);

        echo json_encode($json['body']);
?>



