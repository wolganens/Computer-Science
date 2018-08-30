<?php

Class User {
	public $name;
	public $cpf;
	public $email;
	public $date;
	public $password;

	public function __construct($name, $cpf, $date, $email, $password) {
        $this->setName($name);
        $this->setCpf($cpf);
        $this->setEmail($email);
        $this->setDate($date);
        $this->setPassword($password);
	}

    /**
     * Gets the value of name.
     *
     * @return mixed
     */
    public function getName()
    {
        return $this->name;
    }

    /**
     * Sets the value of name.
     *
     * @param mixed $name the name
     *
     * @return self
     */
    private function setName($name)
    {
        $this->name = $name;

        return $this;
    }

    /**
     * Gets the value of cpf.
     *
     * @return mixed
     */
    public function getCpf()
    {
        return $this->cpf;
    }

    /**
     * Sets the value of cpf.
     *
     * @param mixed $cpf the cpf
     *
     * @return self
     */
    private function setCpf($cpf)
    {
        $this->cpf = $cpf;

        return $this;
    }

    /**
     * Gets the value of email.
     *
     * @return mixed
     */
    public function getEmail()
    {
        return $this->email;
    }

    /**
     * Sets the value of email.
     *
     * @param mixed $email the email
     *
     * @return self
     */
    private function setEmail($email)
    {
        $this->email = $email;

        return $this;
    }

    /**
     * Gets the value of date.
     *
     * @return mixed
     */
    public function getDate()
    {
        return $this->date;
    }

    /**
     * Sets the value of date.
     *
     * @param mixed $date the date
     *
     * @return self
     */
    private function setDate($date)
    {
        $this->date = $date;

        return $this;
    }

    /**
     * Gets the value of password.
     *
     * @return mixed
     */
    public function getPassword()
    {
        return $this->password;
    }

    /**
     * Sets the value of password.
     *
     * @param mixed $password the password
     *
     * @return self
     */
    private function setPassword($password)
    {
        $this->password = $password;

        return $this;
    }
    public function save() {
        $_SESSION['users'][] = $this;
    }
}