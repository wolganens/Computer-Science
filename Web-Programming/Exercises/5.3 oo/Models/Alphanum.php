<?php

Class Alphanum {
	public static function validate($alphanum) {
		if ( preg_match('/[^a-zA-Z\d\s]/', $alphanum)) {
			throw new Exception("Este campo deve conter apenas caracteres alfanuméricos.", 1);
		}
		return $alphanum;
	}
}