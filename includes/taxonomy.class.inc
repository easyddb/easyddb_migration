<?php

class EasyDDBTaxonomyMigration extends DrupalTerm7Migration {
  /**
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    if (!$this->vocabularyExist($arguments['destination_vocabulary'])) {
      $this->createVocabulary($arguments);
    }

    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBTaxonomyMigrationGroup');
  }

  private function vocabularyExist($machineName = NULL) {
    if (!isset($machineName)) {
      throw new Exception(t('Vocabulary machine name empty.'));
    }

    $vocabulary = taxonomy_vocabulary_machine_name_load($machineName);

    if (is_object($vocabulary) && isset($vocabulary->vid)) {
      return TRUE;
    }

    return FALSE;
  }

  private function createVocabulary($args) {
    $vocabulary = new stdClass();
    $vocabulary->name = $args['vocabulary_name'];
    $vocabulary->machine_name = $args['destination_vocabulary'];
    $vocabulary->description = $args['vocabulary_description'];

    taxonomy_vocabulary_save($vocabulary);
  }

  private function editorialBaseDefaultPanelVariant() {
    $handler_name = 'term_editorial_base_panel_context';

    $handler = new stdClass();
    $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
    $handler->api_version = 1;
    $handler->name = $handler_name;
    $handler->task = $page;
    $handler->subtask = '';
    $handler->handler = 'panel_context';
    $handler->weight = 99;
    $handler->conf = array(
      'title' => 'Editorial base term panel',
      'no_blocks' => 0,
      'pipeline' => 'ipe',
      'body_classes_to_remove' => '',
      'body_classes_to_add' => '',
      'css_id' => '',
      'css' => '',
      'contexts' => array(),
      'relationships' => array(),
      'access' => array(
        'plugins' => array(
          0 => array(
            'name' => 'entity_bundle:taxonomy_term',
            'settings' => array(
              'type' => array(
                'editorial_base' => 'editorial_base',
              ),
            ),
            'context' => 'argument_term_1',
            'not' => FALSE,
          ),
          1 => array(
            'name' => 'perm',
            'settings' => array(
              'perm' => 'view editorialbase panels terms',
            ),
            'context' => 'logged-in-user',
            'not' => FALSE,
          ),
        ),
        'logic' => 'and',
      ),
    );
    $display = new panels_display();
    $display->layout = '25_50_25';
    $display->layout_settings = array();
    $display->panel_settings = array(
      'style_settings' => array(
        'default' => NULL,
        'left_sidebar' => NULL,
        'main_content' => NULL,
        'right_sidebar' => NULL,
        'attachment_4_1' => NULL,
        'attachment_4_2' => NULL,
        'attachment_4_3' => NULL,
        'attachment_4_4' => NULL,
        'attachment_3_1' => NULL,
        'attachment_3_2' => NULL,
        'attachment_3_3' => NULL,
        'attachment_2_1' => NULL,
        'attachment_2_2' => NULL,
        'attachment_1_1' => NULL,
      ),
    );
    $display->cache = array();
    $display->title = '';
    $display->content = array();
    $display->panels = array();
      $pane = new stdClass();
      $pane->pid = 'new-1';
      $pane->panel = 'main_content';
      $pane->type = 'views_panes';
      $pane->subtype = 'tags_list-ding_content_tags';
      $pane->shown = TRUE;
      $pane->access = array();
      $pane->configuration = array(
        'context' => array(
          0 => 'argument_term_1',
        ),
      );
      $pane->cache = array();
      $pane->style = array(
        'settings' => NULL,
      );
      $pane->css = array();
      $pane->extras = array();
      $pane->position = 0;
      $pane->locks = array();
      $display->content['new-1'] = $pane;
      $display->panels['main_content'][0] = 'new-1';
    $display->hide_title = PANELS_TITLE_FIXED;
    $display->title_pane = '0';
    $handler->conf['display'] = $display;

    return $handler;
  }

  private function createEbPanelVariant($term) {
    if (!is_object($term) || !isset($term->tid)) {
      return FALSE;
    }

    $handler_name = variable_get('editorial_base_term_panel_handler', 'term_editorial_base_panel_context');

    $page = 'term_view';
    $task = page_manager_get_task($page);
    ctools_get_plugins('page_manager', 'task_handlers', 'panel_context');

    $handlers = page_manager_load_sorted_handlers($task, '');

    $handler = isset($handlers[$handler_name]) ? $handlers[$handler_name] : NULL;
    $tid = $term->tid;

    if (empty($handler)) {
      $handler = $this->editorialBaseDefaultPanelVariant();
    }
    // Normally, panels do not support specific panel to node id mapping, so use
    // php code instead.
    $php_code = '$item = menu_get_object(\'taxonomy_term\', 2);if (isset($item->tid) && $item->tid == ' . $tid . ') {return TRUE;}return FALSE;';

    $php_filter = array(
      'name' => 'php',
      'settings' => array(
        'description' => t('Term being viewed has tid "@tid"', array('@tid' => $tid)),
        'php' => $php_code,
      ),
      'not' => FALSE,
    );

    $handler_name = "term_view_panel_context_tid_{$tid}";
    $variant_title = t('Variant for (@term_name)', array('@term_name' => $term->name));
    $pipeline = module_exists('panels_ipe') ? 'ipe' : 'standard';
    unset($handler->did);
    $handler->name = $handler_name;
    $handler->conf['title'] = $variant_title;
    $handler->conf['pipeline'] = $pipeline;
    $handler->conf['access']['plugins'][] = $php_filter;
    $handler->weight = -50;

    page_manager_save_task_handler($handler);
  }

  public function complete($entity, $row) {
    if ($entity->vocabulary_machine_name == 'editorial_base') {
      $this->createEbPanelVariant($entity);
    }
  }
}
