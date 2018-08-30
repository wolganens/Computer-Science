<?php

namespace App\Models\Client;

use App\Models\User\User;

Class Client extends User
{
	public function __construct($name, $email, $password, $phone_number = null, $identity_number = null, $type)
	{
        $this->setName($name);
        $this->setEmail($email);
        $this->setPassword($password);
        $this->setPhoneNumber($phone_number);
        $this->setIdentityNumber($identity_number);
        $this->setType($type);
	}
}