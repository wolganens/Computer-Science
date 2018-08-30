<?php

namespace App\Controllers;

use App\Models\Client\ClientRepository;
use App\Views\Helpers\View;
use App\Models\Http\Redirect;
use App\Models\ServiceCategory\ServiceCategoryRepository;
use App\Models\Service\ServiceRepository;
use App\Models\Address\AddressRepository;
use App\Models\User\Auth;

Class ClientController
{
	private $service_repository;
	private $address_repository;

	public function __construct()
	{
		/**
		 * Apenas clientes(user-type = 1) tem acesso ao painel de clientes
		 */
		if ($_SESSION['user-type'] && $_SESSION['user-type'] != 1) {
			$_SESSION['danger'] = 'Você não tem acesso a esta página';
			Redirect::url('/');
		}
		$this->service_repository = new ServiceRepository();
		$this->address_repository = new AddressRepository();
	}
	public function dashboard()
	{
		View::render('client', 'client' . DIRECTORY_SEPARATOR . 'dashboard');
	}
	/**
	 * Página de listagem e cadastro de novos serviços por parte do cliente;
	 */
	public function services()
	{
		/**
		 * Busca todas as categorias e serviços do cliente
		 */
		$category_repository = new ServiceCategoryRepository();
		$services = $this->service_repository->findByClient(Auth::user()->getId());
		/**
		 * Os dois fors abaixo são para retornar os endereços e categorias no formato para usar no select do html
		 */
		$addresses_obj = $this->address_repository->findByUser(Auth::user()->getId());
		$addresses = [];
		foreach ($addresses_obj as $address) {
			$addresses[$address->getId()] = $address->getAddressString();
		};
		$categories = [];
		foreach ($category_repository->all() as $category) {
			$categories[$category->getId()] = $category->getName();
		};
		View::render('client', 'client' . DIRECTORY_SEPARATOR . 'services', ['categories' => $categories, 'services' => !is_array($services) ? [$services] : $services, 'addresses' => !is_array($addresses) ? [$addresses] : $addresses]);
	}
	public function professionals()
	{
		View::render('client', 'client' . DIRECTORY_SEPARATOR . 'professionals');
	}
	/**
	 * Página de endereços do cliente
	 */
	public function addresses()
	{
		$addresses = $this->address_repository->findByUser(Auth::user()->getId());
		View::render('client', 'client' . DIRECTORY_SEPARATOR . 'addresses', ['addresses' => $addresses]);
	}
}