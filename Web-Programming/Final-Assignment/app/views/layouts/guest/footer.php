		<div class="modal fade" id="new-client-modal">
			<div class="modal-dialog">
				<form method="POST" action="index.php?controller=Client&action=create" id="client-signup-form">
					<div class="modal-content">
						<div class="modal-header">
							<button type="button" class="close" data-dismiss="modal" aria-hidden="true">&times;</button>
							<h4 class="modal-title">Cadastro de cliente</h4>
						</div>
						<div class="modal-body">
							<div class="form-group">
								<label for="client-name">Nome</label>
								<input type="text" required class="form-control" id="client-number" name="name" placeholder="Qual o seu nome? Ex: João da Silva">
							</div>
							<div class="form-group">
								<label for="client-email">Email</label>
								<input type="email" required class="form-control" id="client-email" name="email" placeholder="Este email será seu acesso ao painel">
							</div>
							<div class="form-group">
								<label for="client-phone">Telefone</label>
								<input type="text" required class="form-control" id="client-phone" name="phone" placeholder="Qual o seu telefone?">
							</div>
							<div class="form-group">
								<label for="client-address">Endereço</label>
								<input type="text" required class="form-control" id="client-address" name="address" placeholder="Qual o seu endereço? Ex: Rua Santana 150">
							</div>
							<div class="form-group">
								<label for="client-password">Senha</label>
								<input type="password" required class="form-control" id="client-password" name="password" placeholder="">
							</div>
						</div>
						<div class="modal-footer">
							<button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
							<button type="submit" class="btn btn-primary">Criar minha conta</button>
						</div>
					</div>
				</form>
			</div>
		</div>
		<script src="../../../../bower_components/jquery/dist/jquery.min.js"></script>
		<script src="../../../../bootstrap-sass/assets/javascripts/bootstrap.min.js"></script>
	</body>
</html>