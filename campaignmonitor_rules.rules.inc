<?php
 
/**
 * Implement hook_rules_action_info().
 */
function campaignmonitor_rules_rules_action_info() {
  return array(
    'campaignmonitor_rules_action_subscribe_user_to_list' => array(
      'label' => t('Subscribe user to a list'),
      'group' => t('Campaign Monitor'),
      'parameter' => array(
        'list_id' => array(
          'type' => 'text',
          'label' => t('A list to subscribe to'),
          'description' => t('Choose a list from the list of your Campaign Monitor lists.'),
          'options list' => 'campaignmonitor_rules_campaignmonitor_list_options',
        ),
        'name' => array(
          'type' => 'text',
          'label' => t('Subscribed user name'),
          'description' => t('Enter a name that should be sent to Campaign Monitor.'),
        ),
        'mail' => array(
          'type' => 'text',
          'label' => t('Subscribed user mail'),
          'description' => t('Enter an e-mail that should be sent to Campaign Monitor.'),
        ),
      ),
    ),
  );
}
 
// A helper function to provide us with a list of CM lists
function campaignmonitor_rules_campaignmonitor_list_options() {
  $lists = array();
  // Get the CampaignMonitor object connector
  $cm = CampaignMonitor::getConnector();
  $lists_info = $cm->getLists();

  foreach($lists_info as $list_id => $list) {
    $lists[$list_id] = $list['name'];
  }
  
  return $lists;
}

// Action callback
function campaignmonitor_rules_action_subscribe_user_to_list($list_id, $name, $mail) {
  // Get the CampaignMonitor object connector
  $cm = CampaignMonitor::getConnector();

  // Try to subscribe to the list.
  if (!$cm->subscribe($list_id, check_plain($mail), check_plain($name))) {
    form_set_error('', t('You were not subscribed to the list. Please try again later.'));
  }
  drupal_set_message(t('You are now subscribed to the IGS Newsletter.'), 'status');  


}