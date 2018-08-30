<?php

namespace App\Models\User;

use Exception;

Class UserRepository
{
	private $dao;
	private $collection = [];

	function __construct()
	{
		$this->dao = new UserDao();
	}
	public function create($name, $email, $password, $phone_number, $identify_number)
	{
		/**
		 * Cria uma instancia do novo usuário a ser inserido no banco de dados;
		 */
		$user = new User($name, $email, $password, $phone_number, $identify_number);
		/**
		 * Tenta inserir o usuário no banco de dados através da UserDao
		 */
		if (!$this->dao->insert($user)) {
			return $this->dao->getDb()->errorInfo()[2];
		} else {
			$user->setId(intval($this->dao->getDb()->lastInsertId()));
			$this->collection[] = $user;
			return $user;
		}
	}
	public function findByEmail($email)
	{
		$query = sprintf('SELECT * FROM user where email = "%s" limit 1;', $email);
		$results = $this->dao->getDb()->query($query);
		foreach ($results as $key => $user) {
			$id = $user['id'];
			$name = $user['name'];
		    $email = $user['email'];
		    $password = $user['password'];
		    $phone_number = $user['phone_number'];
		    $identity_number = $user['identity_number'];
			$user = new User($name, $email, $password, $phone_number, $identity_number);
			$user->setId($id);
			$this->collection[] = $user;
		}
		return $user ?? false;
	}
}