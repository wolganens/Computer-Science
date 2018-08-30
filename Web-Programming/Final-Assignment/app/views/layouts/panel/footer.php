		<script src="../../../../bower_components/jquery/dist/jquery.min.js"></script>
		<script src="../../../../bower_components/bootstrap-sass/assets/javascripts/bootstrap.min.js"></script>
		<script>
			$('#map-modal').on('show.bs.modal', function (event) {
			  var button = $(event.relatedTarget) // Button that triggered the modal
			  codeAddress(button.text());
			})
		</script>
	</body>
</html>