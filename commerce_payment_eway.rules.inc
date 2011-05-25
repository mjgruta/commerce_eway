<?php

/**
 * Rules integration for eWAY token payments
 */


/**
 * Implements hook_rules_action_info().
 */
function commerce_payment_eway_rules_action_info() {
  $actions = array();

  $actions['commerce_payment_eway_create_customer'] = array(
    'label' => t('Setup for eWAY token billing'),
    'parameter' => array(
      'user' => array(
        'type' => 'user',
        'label' => t('User')),
    ),
    'group' => t('Commerce Payment eWAY'),
    'base' => 'commerce_payment_eway_create_customer',
  );

  return $actions;
}


/*
 * When token billing is used, we need to register new customers.
 */
function commerce_payment_eway_create_customer($account) {
  if ($_SESSION['eway_customer_data']) {
    $customer_data = $_SESSION['eway_customer_data'];
    $settings = $_SESSION['eway_login'];
    $testing = $customer_data['CCNumber'] == COMMERCE_PAYMENT_EWAY_TEST_CCNUMBER;
    module_load_include ('class.inc', 'commerce_payment_eway','includes/eway_base');
    module_load_include ('class.inc', 'commerce_payment_eway', 'includes/eway_token');
    $processor = new eway_token ($testing);
    $processor->testing = $testing;
    $processor->log_to_watchdog = $settings['log_to_watchdog'];
    $processor->customer_id = $settings['customer_id'];
    $processor->user_name = $settings['user_name'];
    $processor->password = $settings['password'];
    // Don't care if this fails
    $success = $processor->create_customer ($account->uid, $customer_data);
    unset ($_SESSION['eway_customer_data']);
  }
}
