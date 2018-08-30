<?php 

Class ValidatorController {

	private $rules;
	private $fields;
	public $errors;

	public function __construct($rules, $fields) {
		$this->rules = $rules;
		$this->fields = $fields;
		$this->validate();
	}
	public function alfanum ($input, $value) {
		if ( preg_match('/[^a-zA-Z\d\s]/', $value)) {
			$this->setError($input, 'Este campo deve conter apenas caracteres alfanuméricos.');
		} else {
			return true;
		}
	}
	public function email($input, $value) {
		if (!filter_var($value, FILTER_VALIDATE_EMAIL)) {
			$this->setError($input, 'Email inválido.');
		} else {
			return true;
		}
	}
	public function cpf($input, $value) {
		$cpf  = preg_replace('/[.-]/', '', $value);
		$i = 0;
		$j = 10;
		$aux = 0;
		if (strlen($cpf) != 11) {
			$this->setError($input, 'Este campo deve conter 11 dígitos');
			return false;
		}
		for ($i = 0 ; $i < 9 ; $i++) {
			$aux += $cpf[$i] * $j;
			--$j;
		}
		$aux = $aux % 11;
		$aux = 11 - $aux;

		if ($aux > 9) {
			$aux = 0;
		}
		$dv_1 = $aux;

		$j = 11;
		$aux = 0;
		for ($i = 0 ; $i < 9 ; $i++) {
			$aux += $cpf[$i] * $j;
			--$j;
		}
		$aux += $dv_1 * $j;
		$aux = $aux % 11;

		$aux = 11 - $aux;

		if ($aux > 9) {
			$aux = 0;
		}
		if (! ($dv_1 == $cpf[9] && $aux == $cpf[10]) ) {
			$this->setError($input, "O CPF inserido é inválido");
		} else {
			return true;
		}
	}
	public function date($input, $value) {
		$now = new DateTime();
		if (! preg_match('/\d\d?\/\d\d?\/\d\d\d\d/', $value)) {
			$this->setError($input, 'A data deve estar no formato dd/mm/aaaa');
			return false;
		}
		$inputDate = DateTime::createFromFormat('d/m/Y', $value);
		
		if ($inputDate < $now) {
			$this->setError($input, 'A data deve ser maior ou igual a de hoje');
			return false;
		}
	}
	public function password($input, $value) {
		$errors = '';
		if (strlen($value) < 8 ){
			$errors.= 'Este campo deve ter pelo menos 8 caracteres';
		}
		if (! preg_match('/[a-zA-Z]/', $value)) {
			$errors.= '<br/>Este campo deve conter letras';
		}
		if (! preg_match('/\d/', $value)) {
			$errors.= '<br/>Este campo deve conter números';
		}
		if (! preg_match('/[^a-zA-Z\d]/', $value)) {
			$errors.= '<br/>Este campo deve conter caracteres especiais';
		}
		if($errors != '') {
			$this->setError($input, $errors);
		} else {
			return true;
		}

	}
	public function fail() {
		return count($this->errors) > 0;
	}
	public function errors() {
		return $this->errors;
	}
	public function listErrors() {
		$list = '<ul>';
		foreach ($this->errors as $key => $error) {
			$list.= '<li><strong>' . $key . ': </strong>' . $error . '</li>';
		}
		$list.= '</ul>';
		return $list;
	}
	private function validate() {
		foreach ($this->fields as $key => $value) {
			if (array_key_exists($key, $this->rules)) {
				$this->{$this->rules[$key]}($key, $value); 
			}
		}		
	}
	private function setError($input, $message) {
		$this->errors[$input] = $message;
	}
	public function passes() {
		$passes = empty($this->errors);
		return $passes;
	}
	public function validatorTable() {
		$table = 
			'<table class="table" style="font-size: 2em;">
				<thead>
					<tr>
						<th>Nome do campo</th>
						<th>Válido</th>
						<th>Mensagem</th>
					</tr>
				</thead>
				<tbody>
			';
		foreach ($this->fields as $key => $value) {
			$valid = !array_key_exists($key, $this->errors);
			$validIcon = $valid ? '<span class="text-success glyphicon glyphicon-ok-circle"></span>' : '<span class="text-danger glyphicon glyphicon-remove-circle"></span>';
			$message = $valid ? '<span class="text-success">Campo válido</span>' : '<span class="text-danger">'. $this->errors[$key] . '</span>';
			$table.=sprintf(
				'<tr>
					<td>
						%s
					</td>
					<td>
						%s
					</td>
					<td>
						%s
					</td>
				</tr>', $key, $validIcon, $message);
		}
		$table.= '</tbody></table>';
		return $table;
	}
}