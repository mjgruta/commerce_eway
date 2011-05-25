<?php

class eway_merchant_xml extends eway_xml_common {

   function __construct($testing) {
     parent::__construct($testing);
     $this->url = ($testing) ? 'https://www.eway.com.au/gateway/xmltest/testpage.asp' : 'https://www.eway.com.au/gateway/xmlpayment.asp';
   }

}