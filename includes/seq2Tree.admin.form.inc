<?php


function seq2Tree_admin_form($form, $form_state) {

  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => 'General'
  );

 
 $form['general']['Word_size']= array(
    '#type' => 'textfield',
    '#title' => t('Enter the Default Word Size'),
    '#description' => t('You can define the word size here which is used by Gene Family consensus for Blast'),
    '#default_value' => variable_get('WebserviceDemo_Word_size', 3),
  );
  
  $form['general']['Matrix_options']= array(
    '#type' => 'textfield',
    '#title' => t('Matrix_options'),
    '#description' => t('You can define the Matrix_options here which is used by Gene Family consensus for Blast'),
     '#default_value' => variable_get('WebserviceDemo_Matrix_options', 'PAM30'),
  );
  
    $form['general']['path'] = array(
  '#type' => 'textfield',
  '#title' => t('Enter the path'),
   '#description' => t('This directory path is used to store BLAST output, Rembember to give read and write permission to specified folder'),
    '#default_value' => variable_get('blast_output_path'),
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

  variable_set('blast_output_path', $form_state['values']['path']);
  variable_set('WebserviceDemo_endpoint', $form_state['values']['endpoint']);
  variable_set('WebserviceDemo_Word_size', $form_state['values']['Word_size']);
  variable_set('WebserviceDemo_Matrix_options', $form_state['values']['Matrix_options']);
  variable_set('WebserviceDemo_output_format', $form_state['values']['output_format']);
 
  
  variable_set('WebserviceDemo_nucleotide_example_sequence', $form_state['values']['nucleotide_example']);
  variable_set('WebserviceDemo_protein_example_sequence', $form_state['values']['protein_example']);
  
}
