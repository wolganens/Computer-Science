<?php

namespace App\Controllers;

use App\Models\Http\Redirect;
use App\Models\Http\Input;
use App\Models\Professional\ProfessionalRepository;
use App\Models\Address\AddressRepository;
use App\Models\Service\ServiceRepository;
use App\Views\Helpers\View;
use App\Models\User\Auth;

Class ServiceController
{
	private $professional_repository;
	private $service_repository;
	private $address_repositorty;

	public function __construct()
	{
		$this->professional_repository = new ProfessionalRepository();
		$this->service_repository = new ServiceRepository();
		$this->address_repositorty = new AddressRepository();
	}
	public function postCreate()
	{
		/**
		 * Endereço brevemente cadastrado ou um novo endereço para o serviço
		 */
		if (!is_null(Input::get('address')) && !empty(Input::get('address'))) {
			$address = Input::get('address');
		} else {
			$postal_code = Input::get('postal-code');
			$district = Input::get('district');
			$street = Input::get('street');
			$number = Input::get('number');
			$complement = Input::get('complement');

			$address = $this->address_repositorty->create($postal_code, $complement, $district, $number, $street);
			/**
			 * Será necessário apenas o id do endereço no formulário da página de confirmação de solicitação de serviço
			 */
			$address = $address->getId();
		}
		Redirect::url('index.php?controller=Service&action=chooseProfessional', ['category' => $_POST['category'], 'address' => $address]);
	}
	public function chooseProfessional($params)
	{	
		/**
		 * Extrai a categoria e endereço para as variaveis $category e $address
		 */
		extract($params);
		/**
		 * Procura os profissionais que fazem serviços com a categoria solicitada
		 */
		$professionals = $this->professional_repository->findByCategory($category);
		View::render('client', 'client' . DIRECTORY_SEPARATOR . 'select_service_professional', ['professionals' => $professionals, 'category' => $category, 'address' => $address]);
	}
	/**
	 * Confirmar a solitação de serviço informando o profissional e a categoria
	 */
	public function postConfirm()
	{
		$professional = Input::get('professional');
		$category = Input::get('category');
		$address = Input::get('address');
		$client = Auth::user()->getId();

		$service = $this->service_repository->create($category, $address, $client, $professional, null, null,  null);
		$_SESSION['success'] = 'Serviço solicitado com sucesso! Fique de olho no status do serviço na lista abaixo!';
		Redirect::url('index.php?controller=Client&action=services');
	}
	public function postUpdatePrice()
	{
		$price = Input::get('price');
		$service_id = Input::get('service');
		$service = $this->service_repository->updatePrice($service_id, $price);
		if ($service) {
			$_SESSION['success'] = 'Orçamento realizado com sucesso';
			Redirect::url('index.php?controller=Professional&action=services');
		}
	}
}