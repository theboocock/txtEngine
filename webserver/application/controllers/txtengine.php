<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class txtengine extends CI_Controller {

	public function index()
	{
		$this->load->view('game');
	}
        
        public function execute()
        {
            $this->load->library('session');
            
            $output = shell_exec(
				'./txtEngine -exec games/'.
				$this->session->userdata('game').'.xml /var/www/save/'.
				$this->session->userdata('session_id').'.sav "'.
				$this->input->post('command').'"'
			);
			
			$output = str_replace("\n","",$output);
			
			$this->output
    			->set_content_type('application/json')
    			->set_output($output);
        }
 
        public function set_game()
        {
            $this->load->library('session');
            $this->session->sess_destroy();
            $this->session->set_userdata('game', $this->input->post('game'));
			
			echo $this->input->post('game');
        }
        
        public function games() {
            $games = scandir ('games');
            array_shift($games);
            array_shift($games);
            foreach($games as &$input) {
                $input_arr = explode(".", $input);
                $input = $input_arr[0];
            }
            $this->output->set_content_type('application/json')->set_output(json_encode($games));
        }
}

/* End of file textengine.php */
/* Location: ./application/controllers/textengine.php */