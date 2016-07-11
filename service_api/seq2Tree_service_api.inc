<?php

function makeRequest($resource_path,$endpoint, $http_method, $data = array()) {
   
    $data = http_build_query($data, '', '&');

    $headers = array(
      'Accept' => 'application/json',
      'Content-Type' => 'application/x-www-form-urlencoded'
    );

    $options = array(
      'headers' => $headers,
      'method'  => $http_method,
      'data'    => $data,
    );
    
  $response = drupal_http_request($endpoint . '/' . $resource_path, $options);
  $data_response = $response->data;
 // drupal_set_message($data_response);
  return $data_response;
}
   

function handleRestError($response) {
    if ($response->code != 200) {
      watchdog('clients', 'Error with REST request. Error was code @code with error "@error" and message "@message".', array(
        '@code'     => $response->code,
        '@error'    => $response->error,
        '@message'  => isset($response->status_message) ? $response->status_message : '(no message)',
      ));

      throw new Exception(t("Clients connection error, got message '@message'.", array(
        '@message' => isset($response->status_message) ? $response->status_message : $response->error,
      )), $response->code);
    }
  }
?>