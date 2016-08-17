<?php

$path = drupal_get_path('module', 'seq2Tree');
require_once("$path/includes/seq2Tree.utilityfunction.inc");


function seq2Tree_admin_form($form, $form_state) {

  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => 'General'
  );

	$form['general']['database_option'] = array(
	'#type' => 'radios',
	'#title' => t('Select Blast Program Database Type'),
	'#default_value' => variable_get('WebserviceDemo_blast_program','protein'),
	'#options' => array('nucleotide' => t('Nucleotide'),'protein' => t('Protein')),
	 '#ajax' => array(
     'callback' => 'ajax_seq2Tree_setDatabase_callback',
  //   'wrapper'  => 'refresh_data1',
     'method'   => 'replace',
     'effect'   => 'fade',
    ),
);
 
 $val = _get_database_type(variable_get('WebserviceDemo_blast_program','protein'));

  $form['general']['database_type']= array(
    '#type' => 'select',
    '#title' => t('Enter the database type which matches with Blast program'),
    '#description' => t('You can define the Blast program Type'),
    '#options' => $val,
    '#default_value' => variable_get('WebserviceDemo_database_type'),
    '#validated' => TRUE,
    '#prefix' => '<div id="refresh_data1">',
    '#suffix' => '</div>',
  );
 
 $word_val = _word_size(variable_get('WebserviceDemo_blast_program','protein'));
 
 $form['general']['Word_size']= array(
    '#type' => 'select',
    '#title' => t('Enter the Default Word Size'),
    '#description' => t('You can define the word size here which is used by Gene Family consensus for Blast'),
    '#options' => $word_val,
    '#default_value' => variable_get('WebserviceDemo_Word_size'),
    '#validated' => TRUE,
    '#prefix' => '<div id="refresh_data2">',
    '#suffix' => '</div>',
  );
     

  $form['general']['Matrix_options']= array(
    '#type' => 'textfield',
    '#title' => t('Matrix_options'),
    '#description' => t('You can define the Matrix_options here which is used by Gene Family consensus for Blast'),
    '#default_value' => variable_get('WebserviceDemo_Matrix_options', 'PAM30'),
    '#required' => TRUE
  );
  
    $form['general']['path'] = array(
  '#type' => 'textfield',
  '#title' => t('Enter the path'),
  '#description' => t('This directory path is used to store BLAST output, Rembember to give read and write permission to specified folder'),
  '#default_value' => variable_get('blast_output_path'),
  '#required' => TRUE
  );
  
  
  $form['Web_Services'] = array(
    '#type' => 'fieldset',
    '#title' => 'Web Service Setting'
  );
  
  
  
  $form['Web_Services']['endpoint'] = array(
  '#type' => 'textfield',
  '#title' => t('Enter the endpoint'),
  '#description' => t('You can ignore if your $endpoint variable is set. Otherwise, enter the endpoint. For example, http://localhost/restapi'),
  '#default_value' => variable_get('WebserviceDemo_endpoint', 'http://localhost/restapi'),
  '#required' => TRUE
  );
  
  $form['Web_Services']['output_format'] = array(
  '#type' => 'radios',
  '#title' => t('Select Output Format'),
  '#default_value' => variable_get('WebserviceDemo_output_format','json'),
  '#options' => array('json' => t('json'),'asn' => t('asn'),'xml' => t('xml')),
  );
  
    $form['example_sequence'] = array(
    '#type' => 'fieldset',
    '#title' => 'Set Example Sequences',
    '#description' => 'There is the ability to show example sequences built-in to the various BLAST forms. Use the following fields to set these example sequences. This allows you to provide more relevant examples to your users.'
  );
  
    $nucleotide_default = '>partial lipoxygenase Glyma15g03040
TTTCGTATGA GATTAAAATG TGTGAAATTT TGTTTGATAG GACATGGGAA
AGGAAAAGTT GGAAAGGCTA CAAATTTAAG AGGACAAGTG TCGTTACCAA
CCTTGGGAGC TGGCGAAGAT GCATACGATG TTCATTTTGA ATGGGACAGT
GACTTCGGAA TTCCCGGTGC ATTTTACATT AAGAACTTCA TGCAAGTTGA
GTTCTATCTC AAGTCTCTAA CTCTCGAAGA CATTCCAAAC CACGGAACCA
TTCACTTCGT ATGCAACTCC TGGGTTTACA ACTCAAAATC CTACCATTCT
GATCGCATTT TCTTTGCCAA CAATGTAAGC TACTTAAATA CTGTTATACA
TTGTCTAACA TCTTGTTAGA GTCTTGCATG ATGTGTACCG TTTATTGTTG
TTGTTGAACT TTACCACATG GCATGGATGC AAAAGTTGTT ATACACATAA
ATTATAATGC AGACATATCT TCCAAGCGAG ACACCGGCTC CACTTGTCAA
GTACAGAGAA GAAGAATTGA AGAATGTAAG AGGGGATGGA ACTGGTGAGC
GCAAGGAATG GGATAGGATC TATGATTATG ATGTCTACAA TGACTTGGGC
GATCCAGATA AGGGTGAAAA GTATGCACGC CCCGTTCTTG GAGGTTCTGC
CTTACCTTAC CCTCGCAGAG GAAGAACCGG AAGAGGAAAA ACTAGAAAAG
GTTTCTCACT AGTCACTAAT TTATTACTTT TTAATGTTTG TTTTTAGGCA
TCTTTTCTGA TGAAATGTAT ACTTTTGATG TTTTTTTGTT TTAGCATAAC
TGAATTAGTA AAGTGTGTTG TGTTCCTTAG AAGTTAGAAA AGTACTAAGT
ATAAGGTCTT TGAGTTGTCG TCTTTATCTT AACAGATCCC AACAGTGAGA
AGCCCAGTGA TTTTGTTTAC CTTCCGAGAG ATGAAGCATT TGGTCACTTG
AAGTCATCAG ATTTTCTCGT TTATGGAATC AAATCAGTGG CTCAAGACGT
CTTGCCCGTG TTGACTGATG CGTTTGATGG CAATCTTTTG AGCCTTGAGT
TTGATAACTT TGCTGAAGTG CGCAAACTCT ATGAAGGTGG AGTTACACTA
CCTACAAACT TTCTTAGCAA GATCGCCCCT ATACCAGTGG TCAAGGAAAT
TTTTCGAACT GATGGCGAAC AGTTCCTCAA GTATCCACCA CCTAAAGTGA
TGCAGGGTAT GCTACATATT TTGAATATGT AGAATATTAT CAATATACTC
CTGTTTTTAT TCAACATATT TAATCACATG GATGAATTTT TGAACTGTTA';

  $form['example_sequence']['nucleotide_example'] = array(
    '#type' => 'textarea',
      '#required' => TRUE,
    '#title' => 'Nucleotide Example',
    '#description' => t('Enter a complete nucleotide FASTA record including the header. More information: <a href="@fasta-format-url" target="_blank">FASTA format</a>.',
      array('@fasta-format-url' => 'http://www.ncbi.nlm.nih.gov/BLAST/blastcgihelp.shtml')),
    '#default_value' => variable_get(
        'blast_ui_nucleotide_example_sequence',
        $nucleotide_default
      )
  );

  $protein_default = '>gi|166477|gb|AAA96434.1| resveratrol synthase [Arachis hypogaea]
MVSVSGIRKVQRAEGPATVLAIGTANPPNCIDQSTYADYYFRVTNSEHMTDLKKKFQRICERTQIKNRHM
YLTEEILKENPNMCAYKAPSLDAREDMMIREVPRVGKEAATKAIKEWGQPMSKITHLIFCTTSGVALPGV
DYELIVLLGLDPCVKRYMMYHQGCFAGGTVLRLAKDLAENNKDARVLIVCSENTAVTFRGPSETDMDSLV
GQALFADGAAAIIIGSDPVPEVEKPIFELVSTDQKLVPGSHGAIGGLLREVGLTFYLNKSVPDIISQNIN
DALNKAFDPLGISDYNSIFWIAHPGGRAILDQVEQKVNLKPEKMKATRDVLSNYGNMSSACVFFIMDLMR
KRSLEEGLKTTGEGLDWGVLFGFGPGLTIETVVLRSVAI';

  $form['example_sequence']['protein_example'] = array(
    '#type' => 'textarea',
      '#required' => TRUE,
    '#title' => 'Protein Example',
    '#description' => t('Enter a complete protein FASTA record including the header. More information: <a href="@fasta-format-url" target="_blank">FASTA format</a>.',
      array('@fasta-format-url' => 'http://www.ncbi.nlm.nih.gov/BLAST/blastcgihelp.shtml')),
    '#default_value' => variable_get(
        'blast_ui_protein_example_sequence',
        $protein_default
      )
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save Configuration'
  );

  return $form;
  
  }
  
  /**
 * Validate the Admin/Settings form.
 */
function seq2Tree_admin_form_validate($form, &$form_state) {
	
}




function seq2Tree_admin_form_submit($form, $form_state) {
  variable_set('WebserviceDemo_database_type',$form_state['values']['database_type']);
  variable_set('WebserviceDemo_blast_program',$form_state['values']['database_option']);
  variable_set('blast_output_path', $form_state['values']['path']);
  variable_set('WebserviceDemo_endpoint', $form_state['values']['endpoint']);
  variable_set('WebserviceDemo_Word_size', $form_state['values']['Word_size']);
  variable_set('WebserviceDemo_Matrix_options', $form_state['values']['Matrix_options']);
  variable_set('WebserviceDemo_output_format', $form_state['values']['output_format']);
 
  
  variable_set('WebserviceDemo_nucleotide_example_sequence', $form_state['values']['nucleotide_example']);
  variable_set('WebserviceDemo_protein_example_sequence', $form_state['values']['protein_example']);
  
}

function ajax_seq2Tree_setDatabase_callback($form, $form_state) {

$view = $form_state['values']['database_option'];
$val_data1 = _get_database_type($view);
$val_data2 = _word_size($view);

$form['general']['Word_size']['#options'] = $val_data2;
$form['general']['database_type']['#options'] =  $val_data1;

return array(
    '#type' => 'ajax',
    '#commands' => array(
      ajax_command_replace("#refresh_data1", render($form['general']['database_type'])),
      ajax_command_replace("#refresh_data2", render( $form['general']['Word_size'])),
    )
  );

}
