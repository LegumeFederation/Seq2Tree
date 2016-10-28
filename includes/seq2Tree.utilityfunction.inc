<?php
/** Created and developed By Prateek Gupta
**
**/
function _get_database_type($which){

switch($which){
  case 'protein':
  return array(
     'All proteins'  =>    t('All proteins'),
         'Arachis duranensis - proteins' => t('Arachis duranensis - proteins'),
         'Arachis ipaensis - proteins' => t('Arachis ipaensis - proteins'),
          'Cajanus cajan - proteins' => t('Cajanus cajan - proteins'),
          'Cicer arietinum - proteins' => t('Cicer arietinum - proteins'),
          'Gene Family Consensus' => t('Gene Family Consensus'),
          'Glycine max Wm82.a2 - proteins' => t('Glycine max Wm82.a2 - proteins'),
          'Lotus japonicus v2.5 - proteins' => t('Lotus japonicus v2.5 - proteins'),
          'Medicago truncatula - proteins' => t('Medicago truncatula - proteins'),
          'Phaseolus vulgaris - proteins' => t('Phaseolus vulgaris - proteins')
          );
  case 'nucleotide':
     return array(
            'All CDS' => t('All CDS'),
            'All genomes' => t('All genomes'),
            'Arachis duranensis - CDS' => t('Arachis duranensis - CDS'),
            'Arachis duranensis - genome' => t('Arachis duranensis - genome'),
            'Arachis ipaensis - CDS' => t('Arachis ipaensis - CDS'),
            'Arachis ipaensis - genome' => t('Arachis ipaensis - genome'),
            'Cajanus cajan - CDS' => t('Cajanus cajan - CDS'),
            'Cajanus cajan - genome' => t('Cajanus cajan - genome'),
            'Cicer arietinum - CDS' => t('Cicer arietinum - CDS'),
            'Cicer arietinum - genome' => t('Cicer arietinum - genome'),
            'Glycine max Wm82.a2 - CDS' => t('Glycine max Wm82.a2 - CDS'),
            'Glycine max Wm82.a2 - genome' => t('Glycine max Wm82.a2 - genome'),
            'Lotus japonicus v2.5 - CDS' => t('Lotus japonicus v2.5 - CDS'),
           'Lotus japonicus v2.5 - genome' => t('Lotus japonicus v2.5 - genome'),
            'Medicago truncatula v4.0 - CDS' => t('Medicago truncatula v4.0 - CDS'),
            'Medicago truncatula v4.0 - genome' => t('Medicago truncatula v4.0 - genome'),
          'Phaseolus vulgaris - CDS'  => t('Phaseolus vulgaris - CDS'),
           'Phaseolus vulgaris - genome' => t('Phaseolus vulgaris - genome'),
    );
   }
}

function _get_maxtarget($which) {
  switch ($which) {
    case 'protein':
    case 'nucleotide':
      return array(
        10 => t('10'),
        50 => t('50'),
        100 => t('100'),
        250 => t('250'),
        500 => t('500'),
        1000 => t('1000'),
        5000 => t('5000'),
        10000 => t('10000'),
        20000 => t('20000'),
      );
  }//switch
}

function _get_match_mismatch_Scores($which) {
  switch ($which) {
    case 'nucleotide':
  return array (
            '1,-2' => t('1,-2'),
            '1,-3' => t('1,-3'),
            '1,-4' => t('1,-4'),
            '2,-3' => t('2,-3'),
            '4,-5' => t('4,-5'),
            '1,-1' => t('1,-1'),
        );
    }
}

function _word_size($which){
  switch($which){
  case 'protein':
  return array(
    3 => t('3'),
    6 => t('6'),
  
  );
  case 'nucleotide' :
  return array(
      7 => t('7'),
            11 => t('11'),
            15 => t('15'),
            16 => t('16'),
            20 => t('20'),
            24 => t('24'),
            28 => t('28'),
            32 => t('32'),
            48 => t('48'),
            64 => t('64'),
            128 => t('128'),
            256 => t('256'),
  );
}


}

function _get_gap_costs($which) {
  switch ($which) {
    case 'nucleotide':
  return array (
      'Existence: 5 Extension: 2'  => t('Existence: 5 Extension: 2'),
            'Existence: 2 Extension: 2' => t('Existence: 2 Extension: 2'),
            'Existence: 1 Extension: 2' => t('Existence: 1 Extension: 2'),
            'Existence: 0 Extension: 2'=> t('Existence: 0 Extension: 2'),
            'Existence: 3 Extension: 1' => t('Existence: 3 Extension: 1'),
            'Existence: 2 Extension: 1' => t('Existence: 2 Extension: 1'),
            'Existence: 1 Extension: 1' => t('Existence: 1 Extension: 1'),

       );
    }
}
    
function validate_query_sequence($type, $sequence) {

  if ($type == 'nucleotide') {
    $fastaIdRegEx = '/^>.*(\\n|\\r)/';
    $fastaSeqRegEx = '/[^acgntuACGNTU\n\r]/';
    if ( preg_match($fastaSeqRegEx,$sequence) && !(preg_match($fastaIdRegEx,$sequence)) ) {
      return TRUE;
    } else {
      return FALSE;
    }
  } elseif ($type == 'protein') {
    $fastaIdRegEx = '/^>.*(\\n|\\r)/';
    $fastaSeqRegEx = '/[^acgturykmswbdhvnxACGTURYKMSWBDHVNX\*\-\n\r]/';
    if ( preg_match($fastaSeqRegEx,$sequence) && !(preg_match($fastaIdRegEx,$sequence)) ) {
      return TRUE;
    } else {
      return FALSE;
    }
  }
   return FALSE;
}