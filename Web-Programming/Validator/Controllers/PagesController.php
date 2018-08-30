<?php

require_once('ValidatorController.php');

Class PagesController {	
	public function __construct() {
	}
	public function home() {
		return View::render('home');
	}
	public function register() {
		$rules = [
			'name' 		=> 'alfanum',
			'date' 		=> 'date',
			'cpf' 		=> 'cpf',
			'email' 	=> 'email',
			'password' 	=> 'password'
		];
		$validator = new ValidatorController($rules, $_POST);
		if ($validator->passes()) {
			$user = new User(
				$_POST['name'],
				$_POST['cpf'],
				$_POST['date'],
				$_POST['email'],
				$_POST['password']
			);
			$user->save();
			return View::render('users', ['users' => $_SESSION['users']]);
		}
		
		$_SESSION['errors'] = $validator->errors;
		return View::render('home');
	}
}