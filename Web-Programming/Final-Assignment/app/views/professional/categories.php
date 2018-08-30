<h1 class="page-header">Categorias de Serviço</h1>
<div class="base">
	<p class="text-info">Marque abaixo quais os tipos de serviço que você oferece</p>
	<form action="index.php?controller=Professional&action=postUpdateCategories" method="POST">
		<?php echo $categories; ?>
		<button type="submit" class="btn btn-primary">Salvar</button>
	</form>
</div>