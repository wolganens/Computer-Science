<?php

Class Email {
	public static function validate($email) {
		if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
			throw new Exception('Email inválido.', 1);
		}
		return $email;
	}
}