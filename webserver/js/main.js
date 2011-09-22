$(document).ready(function() {
        $.getJSON('index.php/txtengine/games', function(data) {
			var i= 0;
			$.each(data, function(key, val) {
			 $("#games").append($('<div class="game" />').text(val).prepend('<button id="'+val+'" class="awesome blue play" style="margin-top:-2px;">Play Game</button>').delay(i).fadeIn(500));
			 i+=200;
			});
			$('.play').click(function() {
				$(".game").fadeOut(300);
				$.post('index.php/txtengine/set_game', { game: $(this).attr('id') }, function(data) {
					$('#gamename').text(data);
					setup();
				});
			});
        });

        $("#inputcommand").hide();
});

function setup()
{
	$('#games').animate({ marginTop:10 }, 500);
	$('#content, #inputcommand, #areatitle, #areadesc, #gamename').delay(500).fadeIn(500, function() {
		$('#inputcommand').focus();
	});
	
	$.post('index.php/txtengine/execute', { command: '' }, function(data) {
				$('#areatitle').text(data.areaname);
				$('#areadesc').text(data.areadescription);
	});
	
    $("#inputcommand").keyup(function(event){
		if(event.keyCode == 13){
			$('#content').append($('<div class="cmd" />').text($('#inputcommand').val()).hide().fadeIn(500));
			$.post('index.php/txtengine/execute', { command: $('#inputcommand').val() }, function(data) {
				$('#areatitle').text(data.areaname);
				$('#areadesc').text(data.areadescription);
				$('#content').append($('<div />').html(data.response).hide().fadeIn(500));
				$("#content").scrollTop($("#content").scrollHeight);
			}, "json");
			$('#inputcommand').val('');
		}
	
		return true;
    });
}