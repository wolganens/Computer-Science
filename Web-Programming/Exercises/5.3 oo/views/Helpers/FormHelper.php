<?php

Class FormHelper {
	public function construct() {
	}
	public static function text($label, $name, $value = null, $options = null) {		
		$id = isset($options['id']) ? $options['id'] : $name;
		
		if (isset($_SESSION['errors'][$name])) {
			$error = sprintf('<div class="alert alert-danger">%s</div>', $_SESSION['errors'][$name]);
		} else {
			$error = '';
		}
		
		return sprintf(
			'<div class="form-group">
				<label for="%s">%s</label>
				<input type="text" class="form-control" id="%s" name="%s" value="%s" placeholder="%s">
				%s
			</div>',
			$id, $label, $id, $name, $value, isset($options['placeholder']) ? $options['placeholder'] : null, $error
		);
	}
	public static function password($label, $name, $options = null) {
		$id = isset($options['id']) ? $options['id'] : $name;
		if (isset($_SESSION['errors'][$name])) {
			$error = sprintf('<div class="alert alert-danger">%s</div>', $_SESSION['errors'][$name]);
		} else {
			$error = '';
		}
		return sprintf(
			'<div class="form-group">
				<label for="%s">%s</label>
				<input type="password" class="form-control" id="%s" name="%s" placeholder="%s">
				%s
			</div>',
			$id, $label, $id, $name, isset($options['placeholder']) ? $options['placeholder'] : null, $error
		);
	}
	public static function submit($text) {
		return sprintf('<button type="submit" class="btn btn-primary">%s</button>', $text);
	}
}