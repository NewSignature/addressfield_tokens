<?php 
/**
 * Implements theme_field();
 * 
 * Themes an address field into "city state, country"
 */
function theme_addressfield_formatter__citystate($vars) {
  $loc = $vars['address'];
  
  // Determine which location components to render
  $out = array();
  if (!empty($loc['locality'])) {
    $out[] = $loc['locality'];
  }
  if (!empty($loc['administrative_area'])) {
    $out[] = $loc['administrative_area'];
  }
  if ($loc['country'] != "US" && $country_name = _addressfield_tokens_country($loc['country'])) {
    $out[] = $country_name;
  }
  
  // If there's no location, render an alternate
  if (empty($out)) {
    $out[] = 'Undefined';
  }
  
  // Render the location components
  $output = '<span class="addressfield-citystate">' . implode(', ', $out) . '</span>';
  
  return $output;
}

/**
 * Implements theme_field();
 * 
 * Themes an address field into "name, street1, street2, city state zip country"
 */
function theme_addressfield_formatter__linear($vars) {
  $loc = $vars['address'];
  
  // Determine which location components to render
  $out = array();
  if (!empty($loc['name_line'])) {
    $out[] = $loc['name_line'];
  }
  if (!empty($loc['organisation_name'])) {
    $out[] = $loc['organisation_name'];
  }
  if (!empty($loc['thoroughfare'])) {
    $out[] = $loc['thoroughfare'];
  }
  if (!empty($loc['premise'])) {
    $out[] = $loc['premise'];
  }
  if (!empty($loc['locality'])) {
    $out[] = $loc['locality'];
  }
  if (!empty($loc['administrative_area'])) {
    $out[] = $loc['administrative_area'];
  }
  if (!empty($loc['postal_code'])) {
    $out[] = $loc['postal_code'];
  }
  if ($loc['country'] != "US" && $country_name = _addressfield_tokens_country($loc['country'])) {
    $out[] = $country_name;
  }
  
  // Render the location components
  $output = implode(', ', $out);
  
  return $output;
}