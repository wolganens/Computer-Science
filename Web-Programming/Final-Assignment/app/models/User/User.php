<?php

namespace App\Models\User;

abstract Class User
{
	protected $id;
	protected $name;
    protected $email;
    protected $password;
    protected $phone_number;
    protected $identity_number;
    protected $type;

	public function __construct($name, $email, $password, $phone_number = null, $identity_number = null, $type)
	{
		$this->setName($name);
        $this->setEmail($email);
        $this->setPassword($password);
        $this->setPhoneNumber($phone_number);
        $this->setIdentityNumber($identity_number);
        $this->setType($type);
	}
    public function getId()
    {
        return $this->id;
    }
    public function getName()
    {
        return $this->name;
    }
    public function getEmail()
    {
        return $this->email;
    }
    public function getPassword()
    {
        return $this->password;
    }
    public function getPhoneNumber()
    {
        return $this->phone_number;
    }
    public function getIdentityNumber()
    {
        return $this->identity_number;
    }
    public function setId($id)
    {
        $this->id = $id;

        return $this;
    }
    public function setName($name)
    {
        $this->name = $name;

        return $this;
    }
    public function setEmail($email)
    {
        $this->email = $email;

        return $this;
    }
    public function setPassword($password)
    {
        $this->password = $this->hashPassword($password);
    }
    public function setPhoneNumber($phone_number)
    {
        $this->phone_number = $phone_number;

        return $this;
    }
    public function setIdentityNumber($identity_number)
    {
        $this->identity_number = $identity_number;

        return $this;
    }
    public function signIn($password)
    {
        $hashedPassword = $this->hashPassword($password);
        if (crypt($password, $hashedPassword) == $hashedPassword) {
            $_SESSION['user'] = serialize($this);
            $this->auth_status = true;
            return true;            
        } else {
            return false;
        }
    }
    public static function signOut() 
    {
        $_SESSION = [];
        session_destroy();
    }
    private function hashPassword($password)
    {
        if (defined("CRYPT_BLOWFISH") && CRYPT_BLOWFISH) {
            $salt = '$2y$11$' . substr(md5(uniqid(rand(), true)), 0, 22);
            return crypt($password, $salt);
        }
        echo "CRYPT_BLOWFISH MISSING";
        exit;
    }
    public function setType($type)
    {
        $this->type = $type;
        return $this;
    }
    public function getType()
    {
        return $this->type;
    }
}