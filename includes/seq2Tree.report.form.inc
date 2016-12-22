<?php
/**
 * Implements hook_form().
 * Hooks provided by Drupal for the definition hook_form.
 *
 * Author: Prateek Gupta
 * Created: 2016
 */


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

/**
** This method will fetch the output from BLAST service
*/

function seq2Tree_getResultoutput(){

// Set variable to fetch result
$allow = 'true';
$endpoint = variable_get('WebserviceDemo_endpoint');
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

drupal_set_message($response);
drupal_set_message($destination);

/* Copy the result into File */
$handle = fopen($destination, 'w');

if($handle == null){
  drupal_set_message('Please provide Permission to read and write in Folder :'.$path.'  OR make sure that the path is set correct in configuration of Seq2Tree module');
}
else{
  // Copy JSON 
  if(strcasecmp(variable_get('WebserviceDemo_output_format'), 'json') == 0 )
  {
  $response = drupal_json_decode($response);
  fwrite($handle, serialize($response));
  } // COPY ASN
  else if(strcasecmp(variable_get('WebserviceDemo_output_format'), 'asn') == 0){
    fwrite($handle, $response);
   } // COPY XML
   else{
    fwrite($handle, $response);
   }
fclose($handle);
}




return variable_get('WebserviceDemo_endpoint').'/'.$resource_path;  

} 
?>