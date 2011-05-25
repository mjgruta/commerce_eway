<?php

abstract class eway_base {

  function __construct($testing) {
    $this->return_info = false;
  }

  function charge ($settings, $description, $charge, $credit_card, $address, $order_id, $uid, $mail) {
    $this->prepare_request ($settings, $description, $charge, $credit_card, $address, $order_id, $uid, $mail);
    $this->process_request ();
  }

  abstract protected function prepare_request ($settings, $description, $charge, $credit_card, $address, $order_id, $uid, $mail);

  abstract protected function process_request ();

}