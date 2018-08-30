<?php

namespace App\Controllers;

use App\Models\Professional\ProfessionalRepository;
use App\Models\Client\ClientRepository;
use App\Models\ServiceCategory\ServiceCategoryRepository;
use App\Models\Service\ServiceRepository;
use App\Models\Address\AddressRepository;
use App\Models\Service\Service;
use App\Models\Professional\Professional;
use App\Views\Helpers\View;
use App\Models\Http\Redirect;
use App\Models\User\Auth;

Class ProfessionalController
{
	private $professional_repository;
	private $service_repository;
	private $address_repository;
	private $client_repository;

	public function __construct()
	{
		if ($_SESSION['user-type'] && $_SESSION['user-type'] != 2) {
			$_SESSION['danger'] = 'Você não tem acesso a esta página';
			Redirect::url('/');
		}
		$this->professional_repository = new ProfessionalRepository();
		$this->service_repository = new ServiceRepository();
		$this->client_repository = new ClientRepository();
	}
	public function dashboard()
	{
		View::render('professional', 'professional' . DIRECTORY_SEPARATOR . 'dashboard');
	}
	/**
	 * Serviços de um profissional
	 */
	public function services()
	{
		/**
		 * Verifica se o objeto está no repositório de serviços da sessão (melhora grande de desempenho)
		 */
		$service_repo_session = isset($_SESSION['repositories']) && isset($_SESSION['repositories']['service']) ? unserialize($_SESSION['repositories']['service']) : null;
		if (!is_null($service_repo_session)) {
			$services = [];
			foreach ($service_repo_session as $service) {
				if ($service->getProfessional()->getId() == Auth::user()->getId()) {
					$services[] = $service;
				}
			}
		} else {
			$services = $this->service_repository->findByProfessional(Auth::user()->getId());
		}
		View::render('professional', 'professional' . DIRECTORY_SEPARATOR . 'services', ['services' => !is_array($services) ? [$services] : $services]);
	}
	public function clients()
	{
		$clients = $this->client_repository->findByProfessional(Auth::user()->getId());
		View::render('professional', 'professional' . DIRECTORY_SEPARATOR . 'clients', ['clients' => is_array($clients) ? $clients : [$clients]]);
	}
	/**
	 * Carrega a página de categorias de serviço de um profissional
	 */
	public function categories()
	{
		/**
		 * Busca as categorias e verifica se o profissional logado trabalha em alguma delas
		 * para já deixar o checkbox marcado.
		 */
		$category_repository = new ServiceCategoryRepository();
		$categories = $category_repository->all();
		$category_form = '';
		foreach ($categories as $key => $category) {
			$checked = in_array($category->getId(), Auth::user()->getCategories());
			$category_form.= sprintf(
			'<div class="checkbox">
				<label>
				<input %s name="categories[]" value="%s" type="checkbox">%s
				</label>
			</div>', $checked ? 'checked="checked"' : '' , $category->getId(), $category->getName()
			);
		}
		View::render('professional', 'professional' . DIRECTORY_SEPARATOR . 'categories', ['categories' => $category_form]);
	}
	public function postUpdateCategories()
	{
		$categories = $_POST['categories'] ?? [];
		Auth::updateAuthUser($this->professional_repository->updateCategories(Auth::user(), $categories));
		$_SESSION['success'] = 'Suas categorias foram atualizadas com sucesso!';
		Redirect::url('index.php?controller=Professional&action=categories');
	}
}