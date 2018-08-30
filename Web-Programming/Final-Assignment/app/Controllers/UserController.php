<?php

namespace App\Controllers;

use App\Models\User\UserRepository;
use App\Models\Client\ClientRepository;
use App\Models\Professional\ProfessionalRepository;
use App\Models\User\User;
use App\Views\Helpers\View;
use App\Models\Http\Input;
use App\Models\Http\Redirect;

Class UserController
{
	private $user_repository;
	private $client_repository;
	private $professional_repository;

	public function __construct()
	{
		$this->user_repository = new UserRepository();
		$this->client_repository = new ClientRepository();
		$this->professional_repository = new ProfessionalRepository();
	}
	public function postCreate()
	{		
		$name = Input::get('name');
		$email = Input::get('email');
		$password = Input::get('password');
		$phone_number = Input::get('phone');
		$identity_number = Input::get('identity-number');
		$user;
		$user_type = $_POST['user-type'];
		switch ($user_type) {
			case 1:
				$user = $this->client_repository->create($name, $email, $password, $phone_number, $identity_number);
				$_SESSION['user-type'] = 1;
				break;
			case 2:
				$user = $this->professional_repository->create($name, $email, $password, $phone_number, $identity_number);
				$_SESSION['user-type'] = 2;
				break;
			default:
				throw new Exception("Tipo de usuário inválido", 1);
				break;
		}
		if (is_object($user)) {
			$user->signIn($password);
		} else {
			$_SESSION['danger'] = $user;
			Redirect::url('index.php?controller=Pages&action=signup');
		}
		if ($_SESSION['user-type'] == 1) {
			Redirect::url('index.php?controller=Client&action=dashboard');
		} else {
			Redirect::url('index.php?controller=Professional&action=dashboard');
		}
	}
	public function postSignIn()
	{
		$email = $_POST['email'];
		$password = $_POST['password'];
		/**
		 * Tenta encontrar o usuário pelo email nos dois tipos de usuário
		 */
		$user = $this->client_repository->findByEmail($email) ?? $this->professional_repository->findByEmail($email) ?? null;
		if ($user) {
			/**
			 * Se encontrar o usuário pelo email, e a senha bater com a do banco, redireciona para o 
			 * devido painel de acordo com o tipo de usuário
			 */
			if ($user->signIn($password)) {
				if ($user->getType() == 1) {
					$_SESSION['user-type'] = 1;
					Redirect::url('index.php?controller=Client&action=dashboard');
				} else if ($user->getType() == 2) {
					$_SESSION['user-type'] = 2;
					Redirect::url('index.php?controller=Professional&action=dashboard');
				}
			} else {
				/**
				 * Se encontrar o usuário e não bater a senha com a do banco, retorna  para o login alertando o usuário.
				 */
				$_SESSION['danger'] = 'Senha incorreta!';
				Redirect::url('index.php?controller=Pages&action=signin');
			}
		} else {
			/**
			 * Se não encontrar o usuário, retorna para o login alertando o mesmo;
			 */
			$_SESSION['danger'] = 'Email não cadastrado!';
			Redirect::url('index.php?controller=Pages&action=signin');
		}
	}
	public function getSignOut()
	{
		User::signOut();
		Redirect::url('/');
	}
	public function getProfile()
	{
		if ($_SESSION['user-type'] == 1) {
			View::render('panel', 'client' . DIRECTORY_SEPARATOR . 'profile'
				);
		} else {
			View::render('panel', 'professional' . DIRECTORY_SEPARATOR . 'profile'
				);
		}
	}
}