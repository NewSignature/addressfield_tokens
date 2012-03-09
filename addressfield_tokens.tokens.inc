<?php
/**
 * @file 
 * 
 * Copyright 2011 New Signature
 * http://www.newsignature.com
 *
 * @author Andrew Marcus
 * @since Oct 4, 2011
 */

/**
 * Implements hook_token_info_alter().
 * 
 * Exposes the billing address for use in tokens.
 * 
 * @param array $info The existing token info.
 */
function addressfield_tokens_token_info_alter(&$info) {
  // Define the address field token types 
  $info['types']['addressfield'] = array(
    'name' => t('Address field'),
    'description' => t('An address associated with an entity.'),
    'needs-data' => 'addressfield',
  );
  
  // Add tokens for each component of the address
  $info['tokens'] += array( 'addressfield' => array() );
  
  $props = addressfield_data_property_info();
  foreach ($props as $field => $data) {
    $field = str_replace('_', '-', $field);
    $name = $data['label'];
    
    $info['tokens']['addressfield'][$field] = array(
  		'name' => $name,
      'description' => $name,
      'type' => 'text',
    );
  }
  
  // Add tokens for the formatted address and text-only version.
  $info['tokens']['addressfield'] += array(
    'full' => array(
      'name' => t('Formatted address'),
      'description' => t('The full formatted address.'),
      'type' => 'text',
    ),
    'text' => array(
      'name' => t('Text-only address'),
      'description' => t('The full address with line breaks but no formatting.'),
      'type' => 'text',
    ),
  );
}

function addressfield_tokens_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  
  // Process address field tokens
  if ($type == 'addressfield') {
    foreach ($tokens as $name => $original) {
      $name = str_replace('-', '_', $name);
      if (isset($data['addressfield'][$name])) {
        $replacements[$original] = $data['addressfield'][$name];
      }
      elseif ($name == 'full') {
        $render = addressfield_generate($data['addressfield'], array('address'), array(
          'mode' => 'render', 
        ));
        $replacements[$original] = drupal_render($render);
      }
      elseif ($name == 'text') {
        $out = array();
        if (!empty($data['addressfield']['thoroughfare'])) {
          $out[0] = $data['addressfield']['thoroughfare'];
        }
        $out[1] = array(); 
        if (!empty($data['addressfield']['locality'])) {
          $out[1][] = $data['addressfield']['locality'];
        }
        if (!empty($data['addressfield']['administrative_area'])) {
          $out[1][] = $data['addressfield']['administrative_area'];
        }
        $out[1] = implode(', ', $out[1]);
        if (!empty($data['addressfield']['postal_code'])) {
          $out[1] .= ' ' . $data['addressfield']['postal_code'];
        }
        if (!empty($data['addressfield']['country']) && $data['addressfield']['country'] != 'US') {
          $countries = _addressfield_country_options_list();
          $out[2] = $countries[$data['addressfield']['country']];
        }
        $replacements[$original] = implode("\n", $out);
      }
      else {
        $replacements[$original] = '';
      }
    }
  }
  return $replacements;
}