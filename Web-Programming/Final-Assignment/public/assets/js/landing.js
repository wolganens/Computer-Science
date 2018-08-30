function addEvent(element, event, callback){
	return element.addEventListener(event,callback);
}
function Service (){
	this.category = null;
	this.client = null;
	this.events();
}
Service.prototype.events = function() {
	var self = this;
	addEvent(document.getElementById('category-select'), 'change', function() {
		if (this.value != -1) {
			self.category = this.value;
			self.showClientRegister();
		}
	});
	addEvent(document.getElementById('client-signin-form'), 'submit', function(event) {
		//event.preventDefault();
	});
	addEvent(document.getElementById('join-form'), 'submit', function(event) {
		event.preventDefault();
		self.showSuccessJoin();
	});
};
Service.prototype.showClientRegister = function() {	
	document.getElementById('client-signin-panel').classList.remove('hidden');
	document.getElementById('category-select').parentNode.classList.add('hidden');
};
Service.prototype.hideClientRegister = function() {
	document.getElementById('category-select').parentNode.classList.remove('hidden');
	document.getElementById('client-signin-panel').classList.add('hidden');
};
Service.prototype.showSuccessJoin = function(first_argument) {
	document.getElementById('success-join-message').classList.remove('hidden');
	document.getElementById('join-form').classList.add('hidden');
};
var serv = new Service();