<?php

$path = drupal_get_path('module', 'seq2Tree');
require_once("$path/service_api/seq2Tree_service_api.inc");
require_once("$path/includes/seq2Tree.utilityfunction.inc");



function seq2Tree_form($form, &$form_state){


$form['DB'] = array(
 	'#title' => t('DataBase Options'),
 	'#type' => 'fieldset',
 	'#collapsible' => TRUE,
    '#collapsed' => FALSE,
);


$form['DB']['database_option'] = array(
'#type' => 'radios',
'#title' => t('Select Query Type'),
'#default_value' => 'nucleotide',
'#options' => array('nucleotide' => t('Nucleotide'),'protein' => t('Protein')),
 '#ajax' => array(
      'callback' => 'ajax_seq2Tree_perprogram_example_sequence_callback',
      'wrapper'  => 'fasta-textarea',
      'method'   => 'replace',
      'effect'   => 'fade',
    ),
);

 $form['DB']['SELECT_DB'] = array(
    '#type' => 'item',
    '#markup' => variable_get('WebserviceDemo_database_type'),
    '#title' => t('BLAST Databases:'),
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
  );


$form['genefamily'] = array(
 	'#title' => t('Enter Query'),
 	'#type' => 'fieldset',
);
 
 $form['genefamily']['example_sequence'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show an Example Sequence'),
    '#prefix' => '<span style="float: right;">',
    '#suffix' => '</span>',
    '#ajax' => array(
      'callback' => 'ajax_seq2Tree_perprogram_example_sequence_callback',
      'wrapper'  => 'fasta-textarea',
      'method'   => 'replace',
      'effect'   => 'fade',
    ),
  );


$form['genefamily']['query'] = array(
    '#type' => 'textarea',
    '#title' => t('Enter FASTA sequence(s)'),
    '#description'=>t('Enter query sequence(s) in the text area.'),
     '#prefix' => '<div id="fasta-textarea">',
    '#suffix' => '</div>',
  );




$form['advanced'] = array(
 	'#title' => t('Advanced Options'),
 	'#type' => 'fieldset',
 	'#collapsible' => TRUE,
    '#collapsed' => FALSE,
);


 $form['advanced']['maxTarget'] = array(
    '#type' => 'select',
    '#title' => t('Max target sequences:'),
    '#options' => _get_maxtarget(variable_get('WebserviceDemo_blast_program')),
    '#default_value' => 10,
    '#description' => t('Select the maximum number of aligned sequences to display'),
  );

$form['advanced']['eVal'] = array(
    '#type' => 'textfield',
    '#title' => t('e-Value (Expected Threshold)'),
    '#size' => 12,
    '#maxlength' => 20,
    '#default_value' => 0.001,
    '#description' => t('Expected number of chance matches in a random model. This number should be give in a decimal format. <a href="http://www.ncbi.nlm.nih.gov/BLAST/blastcgihelp.shtml#expect" target="_blank">More Information</a> | <a href="https://www.youtube.com/watch?v=nO0wJgZRZJs" target="_blank">Expect value video tutorial</a>'),
  );
  
 if(variable_get('WebserviceDemo_blast_program') == 'nucleotide')
 {
  
  $form['Scoring_parameters'] = array(
 	'#title' => t('Scoring_parameters'),
 	'#type' => 'fieldset',
 	'#collapsible' => TRUE,
    '#collapsed' => TRUE,
);

 $form['Scoring_parameters']['Match_Mismatch_Scores'] = array(
    '#type' => 'select',
    '#title' => t('Match_Mismatch_Scores:'),
    '#options' => _get_match_mismatch_Scores('nucleotide'),
    '#default_value' => '1,-2',
    '#description' => t('Reward and penalty for matching and mismatching bases.'),
  );
  
   $form['Scoring_parameters']['Gap_Costs'] = array(
    '#type' => 'select',
    '#title' => t('Gap_Costs:'),
    '#options' => _get_gap_costs('nucleotide'),
    '#default_value' => 'Existence: 5 Extension: 2',
    '#description' => t('Cost to create and extend a gap in an alignment. Linear costs are available only with megablast and are determined by the match/mismatch scores.'),
  );

}
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#default_value' => ' BLAST ',
  );
   


return $form;

}



function seq2Tree_form_validate($form,&$form_state){

}


function seq2Tree_form_submit($form,&$form_state)
{

/*get all the values from configuration */

$query_Type = $form_state['values']['database_option'];
$query = $form_state['values']['query'];
$db = variable_get('WebserviceDemo_database_type');
$maxTarget = $form_state['values']['maxTarget'];
$eVal = $form_state['values']['eVal'];
$Word_size = variable_get('WebserviceDemo_Word_size');
$Matrix_options = variable_get('WebserviceDemo_Matrix_options');
$database_type = variable_get('WebserviceDemo_blast_program');
$output_format = variable_get('WebserviceDemo_output_format');




$endpoint = variable_get('WebserviceDemo_endpoint');
$resource_path = 'blast/getJobId.json';
$http_method = 'POST';
$data = array();


if($database_type == 'nucleotide')
{  
	if($query_Type == 'nucleotide'){
	$data = array('query_type' => $query_Type,
              'db_type' => $database_type,
              'Select_Database' => $db,
              'Max_target_sequences' => $maxTarget,
              "Word_size" => $Word_size,
              'output_format' =>$output_format,
              'Match_Mismatch_Scores' => $form_state['values']['Match_Mismatch_Scores'],
              'Gap_Costs' => $form_state['values']['Gap_Costs'],
              'seqQuery' => $query,
               );
	
	}
	if($query_Type == 'protein'){
	 $data = array('query_type' => $query_Type,
              'db_type' => $database_type,
              'Select_Database' => $db,
              'Max_target_sequences' => $maxTarget,
              "Word_size" => 3,
              'output_format' =>$output_format,
              'Gap_costs' => $form_state['values']['Gap_Costs'],
               "Matrix_options" => $Matrix_options,	
              'seqQuery' => $query,
               );
	
	}
      
} 
if($database_type == 'protein')
{
	if($query_Type == 'nucleotide'){
	$data = array('query_type' => $query_Type,
              'db_type' => $database_type,
              'Select_Database' => $db,
              'Max_target_sequences' => $maxTarget,
              "Word_size" => $Word_size,
              'seqQuery' => $query,
              'output_format' =>$output_format,
              "Matrix_options" => $Matrix_options,	);
	
	}
	if($query_Type == 'protein'){
	$data = array('query_type' => $query_Type,
              'db_type' => $database_type,
              'Select_Database' => $db,
              'Max_target_sequences' => $maxTarget,
              "Word_size" => $Word_size,
              'seqQuery' => $query,
              'output_format' =>$output_format,
              "Matrix_options" => $Matrix_options,	
              "Gap_costs" => 'Existence: 5 Extension: 2',	);
	
	}
															
}

//drupal_set_message('<pre>' . print_r($data, TRUE) . '</pre>');


$result = makeRequest($resource_path,$endpoint,$http_method,$data);

$result = drupal_json_decode($result);

//drupal_set_message('<pre>' . print_r($result, TRUE) . '</pre>');

variable_set('webservice_id',$result['job_Id']);

//drupal_set_message($result['job_Id']);

$resource_path = 'blast/getBlastStatus.json';
$http_method = 'POST';
$data = array('job_id' => $result['job_Id']);
$result = makeRequest($resource_path,$endpoint,$http_method,$data);
$result = drupal_json_decode($result);
$status = $result[0];


while(true){
	if(strcasecmp($status, 'Completed') == 0 ){
		break;
	}else{
		$result = makeRequest($resource_path,$endpoint,$http_method,$data);
		$result = drupal_json_decode($result);
		$status = $result[0];
	}
}  
//drupal_set_message($status);
drupal_goto("seq2Tree/report");   
}




function ajax_seq2Tree_perprogram_example_sequence_callback($form, $form_state) {
  $sequence_type = $form_state['values']['database_option'];
  
  // Choose the example sequence based on the sequence type of the query.
  if ($form_state['values']['example_sequence'] == 1) {
  			if ($sequence_type == 'nucleotide') {
    				$example_sequence = variable_get('WebserviceDemo_nucleotide_example_sequence');
  				}
  			else{
    				$example_sequence = variable_get('WebserviceDemo_protein_example_sequence');
  				}
  		$form['genefamily']['query']['#value'] = $example_sequence;
  	}
  else {
    $form['genefamily']['query']['#value'] = '';
  }
  return $form['genefamily']['query'];
}
