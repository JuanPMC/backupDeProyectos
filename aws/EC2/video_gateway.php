<?php
include 'keys.php';

	function formatearArray2Json($lista){
                $resultado = "[";
                foreach($lista as &$elemento){
                        $resultado = $resultado .'"'. $elemento . '",';
                }
                $resultado = $resultado . '"video"]';
                return $resultado;
        }

        $lambda_func='createVideo';
        $payload='{"videoTitle":"'. $_GET['videoTitle'] . '", "tags": ' . formatearArray2Json($_GET['tags']) . ', "localizacion": "' . $_GET['localizacion'] . '", "usuario": "' . $_GET['usuario'] . '"}';

        $cmd=' AWS_ACCESS_KEY_ID='. $aws_access_key_id .

             ' AWS_SECRET_ACCESS_KEY='. $aws_secret_access_key .

             ' AWS_SESSION_TOKEN='. $aws_session_token . ' aws lambda invoke --region us-east-1 --function-name '. $lambda_func . ' --payload \''. $payload . '\' /tmp/resp.json 2>&1';

        exec( $cmd,$result,$result2);

        header('Access-Control-Allow-Origin: *');

        $result=file_get_contents("/tmp/resp.json");

        $json=json_decode($result,true);

        echo json_encode($json['body']);
	//echo $payload;
?>


