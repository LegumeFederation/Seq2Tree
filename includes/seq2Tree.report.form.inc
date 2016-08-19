<?php

$path = drupal_get_path('module', 'seq2Tree');
require_once("$path/service_api/seq2Tree_service_api.inc");



function seq2Tree_result_form($form, &$form_state){

$output = seq2Tree_getResultoutput();

$form['result'] = array(
 	'#title' => t('Blast Result'),
 	'#type' => 'fieldset',
 	'#collapsible' => TRUE,
    '#collapsed' => FALSE,
);

 $form['result']['headings'] = array(
        '#markup' => '<hgroup><h4>Result of Blast Form on given Inputs</h4>
                      <h5>Click on the file below to get the blast result</h5></hgroup>'
    );  

$form['result']['output'] = array(
      'title' => array(
        'data' => array(
          '#type' => 'link',
          '#title' => 'Blast Output',
          '#href' => $output,
        ),
      ),
    ); 

return $form;

}

function seq2Tree_getResultoutput(){

$allow = 'true';
$endpoint = 'http://localhost/restapi';
$job_id = variable_get('webservice_id');
$http_method = 'GET';
$resource_path = '';


if(strcasecmp(variable_get('WebserviceDemo_output_format'), 'json') == 0 || strcasecmp(variable_get('WebserviceDemo_output_format'), 'asn') == 0){
	$resource_path = 'blast/'.$job_id.'.json';
}
else{
	$resource_path = 'blast/'.$job_id.'.xml';
}


$data = array();
$response = makeRequest($resource_path,$endpoint,$http_method,$data);

$path = variable_get('blast_output_path');
$destination = $path."/".$job_id.".".variable_get('WebserviceDemo_output_format');  

/* Copy the result into File */

$handle = fopen($destination, 'w');

if(strcasecmp(variable_get('WebserviceDemo_output_format'), 'json') == 0 ){
$response = drupal_json_decode($response);
fwrite($handle, serialize($response));
}
else if(strcasecmp(variable_get('WebserviceDemo_output_format'), 'asn') == 0){
fwrite($handle, $response);
}else{
fwrite($handle, $response);
}

fclose($handle);


//drupal_set_message($response);

/*
$handle = fopen($destination, 'w');
if(strcasecmp(variable_get('WebserviceDemo_output_format'), 'json') == 0){
	fwrite($handle, serialize($response));
}elseif(strcasecmp(variable_get('WebserviceDemo_output_format'), 'asn') == 0){
    drupal_set_message($response);
	//fwrite($handle, $response);
}
fclose($handle);
*/


return variable_get('WebserviceDemo_endpoint').'/'.$resource_path;  

} 
?>