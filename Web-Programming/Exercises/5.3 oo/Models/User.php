<?php

require_once('Models' . DIRECTORY_SEPARATOR . 'Cpf.php');
require_once('Models' . DIRECTORY_SEPARATOR . 'Alphanum.php');
require_once('Models' . DIRECTORY_SEPARATOR . 'Email.php');

Class User {
	
    private $name;
	private $cpf;
	private $email;
	private $date;
	private $password;
    private $errors = [];

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
     */
    private function setName($name)
    {
        try {
            $this->name = Alphanum::validate($name);
            $this->resetError('name');
        } catch (Exception $e) {
            $_SESSION['errors']['name'] = $e;
        }
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
     */
    private function setCpf($cpf)
    {
        try {
            $this->cpf = Cpf::validate($cpf);
            $this->resetError('cpf');            
        } catch (Exception $e) {
            $_SESSION['errors']['cpf'] = $e;
        }
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
     */
    private function setEmail($email)
    {
        try {
            $this->email = Email::validate($email);
            $this->resetError('email');
        } catch (Exception $e) {
            $_SESSION['errors']['email'] = $e;
        }
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
     */
    private function setDate($date)
    {
        $now = new DateTime();
        
        try {
            if (! preg_match('/\d\d?\/\d\d?\/\d\d\d\d/', $date)) {
                throw new Exception('A data deve estar no formato dd/mm/aaaa', 1);
            }
    
            $inputDate = DateTime::createFromFormat('d/m/Y', $date);
    
            if ($inputDate < $now) {
                throw new Exception('A data deve ser maior ou igual a de hoje', 1);
            }
            $this->resetError('date');
        } catch (Exception $e) {
            $_SESSION['errors']['date'] = $e;
        }
        $this->date = $date;
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
     */
    private function setPassword($password)
    {
        try {
            if (strlen($password) < 8 ){
                throw new Exception('Este campo deve ter pelo menos 8 caracteres', 1);
            }
            if (! preg_match('/[a-zA-Z]/', $password)) {
                throw new Exception('Este campo deve conter letras', 1);
            }
            if (! preg_match('/\d/', $password)) {
                throw new Exception('Este campo deve conter números', 1);
            }
            if (! preg_match('/[^a-zA-Z\d]/', $password)) {
                throw new Exception('Este campo deve conter caracteres especiais', 1);
            }
            $this->resetError('password');
        } catch (Exception $e) {
            $_SESSION['errors']['password'] = $e;
        }
        $this->password = $password;
    }
    private function resetError($error) {
        unset($_SESSION['errors'][$error]);
    }
    public function save() {
        $_SESSION['users'][] = $this;
    }
}