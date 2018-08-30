<?php

namespace App\Models\Professional;

use App\Models\User\User;

Class Professional extends User
{
	private $categories = [];

	public function __construct($name, $email, $password, $phone_number = null, $identity_number = null, $type)
	{	
        $this->setName($name);
        $this->setEmail($email);
        $this->setPassword($password);
        $this->setPhoneNumber($phone_number);
        $this->setIdentityNumber($identity_number);
        $this->setType($type);
	}	
    public function getCategories()
    {
        return $this->categories;
    }
    public function setCategories($categories)
    {
        $this->categories = $categories;
        return $this;
    }
}