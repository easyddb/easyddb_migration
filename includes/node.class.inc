<?php
/**
 * @file
 * Implementation of node migration.
 */

/**
 * Handling specific to a Drupal 7 source for node with content type news.
 */
class EasyDDBNewsMigration extends DrupalNode7Migration {

  /**
   * @var bool editorial dashboard module enabled.
   */
  private $ed_module = FALSE;

  /**
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $this->ed_module = module_exists('easyddb_editorial_dashboard');
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBNodeMigrationGroup');

    // Dependencies.
    $this->dependencies[] ='fileMigration';
    $this->dependencies[] ='newsCategoryMigration';
    $this->dependencies[] ='tagsMigration';
    $this->dependencies[] ='sectionMigration';
    $this->dependencies[] ='damsCategoryMigration';
    $this->dependencies[] ='libraryMigration';

    //Mapping.
    $this->addFieldMapping('field_ding_news_category', 'field_category')->sourceMigration('newsCategoryMigration');
    $this->addFieldMapping('field_ding_news_category:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_ding_news_category:create_term')->defaultValue(FALSE);

    $this->addFieldMapping('og_group_ref', 'og_group_ref')->sourceMigration('libraryMigration');

    $this->addFieldMapping('field_ding_news_materials', 'field_materials');

    $this->addFieldMapping('field_ding_news_lead', 'field_ding_body:summary');
    $this->addFieldMapping('field_ding_news_body', 'field_ding_body');
    $this->addFieldMapping('field_ding_news_body:format', 'field_ding_body:format');

    $this->addFieldMapping('field_ding_news_list_image', 'field_list_image')
      ->sourceMigration('fileMigration');
    $this->addFieldMapping('field_ding_news_list_image:file_class')
      ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_ding_news_list_image:alt', 'field_list_image:alt');
    $this->addFieldMapping('field_ding_news_list_image:title', 'field_list_image:title');

    $this->addFieldMapping('field_ding_news_tags', 'ding_content_tags')->sourceMigration('tagsMigration');
    $this->addFieldMapping('field_ding_news_tags:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_ding_news_tags:create_term')->defaultValue(FALSE);

    $this->addFieldMapping('field_editorial_base', 'field_editorial_base_n')->sourceMigration('sectionMigration');
    $this->addFieldMapping('field_editorial_base:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_editorial_base:create_term')->defaultValue(FALSE);

    $this->addFieldMapping('field_ding_news_title_image', 'field_main_image')
      ->sourceMigration('fileMigration');
    $this->addFieldMapping('field_ding_news_title_image:file_class')
      ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_ding_news_title_image:alt', 'field_main_image:alt');
    $this->addFieldMapping('field_ding_news_title_image:title', 'field_main_image:title');

    // Migrate Editorial Dashboard statuses.
    if ($this->ed_module) {
      $this->addFieldMapping('field_editorial_status', 'edns_status')
        ->defaultValue('ed_appr');
    }

    $this->removeFieldMapping('body');
    $this->removeFieldMapping('body:language');
    $this->removeFieldMapping('body:summary');
    $this->removeFieldMapping('body:format');
  }

  protected function query() {
    $query = parent::query();
    $query->join('editorial_dashboard_node_status', 'edns', 'n.nid = edns.nid');
    $query->fields('edns', array('status'));

    return $query;
  }

  public function prepare($entity, $row) {
    $ed_nodes = variable_get('editorial_base_content_types');
    $node_ed = !empty($ed_nodes['ding_news']);
    $node_ed_status = $row->edns_status;
    $node_enabled = $entity->status == 1;

    if ($node_ed_status && $this->ed_module && $node_ed) {
      $editorial_status = (int) $entity->field_editorial_status[LANGUAGE_NONE][0]['value'];
      $ed_status_mapping = array(
        1 => 'ed_new',
        2 => 'ed_pushed',
        4 => 'ed_rej',
        8 => 'ed_appr',
      );

      if ($node_enabled) {
        $entity->field_editorial_status[LANGUAGE_NONE][0]['value'] = 'ed_appr';
      }
      else {
        $entity->field_editorial_status[LANGUAGE_NONE][0]['value'] = $ed_status_mapping[$editorial_status];
      }
    }
  }
}

/**
 * Handling specific to a Drupal 7 source for node with content type events.
 */
class EasyDDBEventsMigration extends DrupalNode7Migration {

  /**
   * @var bool editorial dashboard module enabled.
   */
  private $ed_module = FALSE;

  /**
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $this->ed_module = module_exists('easyddb_editorial_dashboard');
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBNodeMigrationGroup');

    // Dependencies.
    $this->dependencies[] ='fileMigration';
    $this->dependencies[] ='eventCategoryMigration';
    $this->dependencies[] ='tagsMigration';
    $this->dependencies[] ='damsCategoryMigration';

    //Mapping.
    $this->addFieldMapping('field_ding_event_location', 'field_address');
    $this->addFieldMapping('field_ding_event_location:administrative_area', 'field_address:administrative_area');
    $this->addFieldMapping('field_ding_event_location:sub_administrative_area', 'field_address:sub_administrative_area');
    $this->addFieldMapping('field_ding_event_location:locality', 'field_address:locality');
    $this->addFieldMapping('field_ding_event_location:dependent_locality', 'field_address:dependent_locality');
    $this->addFieldMapping('field_ding_event_location:postal_code', 'field_address:postal_code');
    $this->addFieldMapping('field_ding_event_location:thoroughfare', 'field_address:thoroughfare');
    $this->addFieldMapping('field_ding_event_location:premise', 'field_address:premise');
    $this->addFieldMapping('field_ding_event_location:sub_premise', 'field_address:sub_premise');
    $this->addFieldMapping('field_ding_event_location:organisation_name', 'field_address:organisation_name');
    $this->addFieldMapping('field_ding_event_location:name_line', 'field_address:name_line');
    $this->addFieldMapping('field_ding_event_location:last_name', 'field_address:last_name');
    $this->addFieldMapping('field_ding_event_location:data', 'field_address:data');
    $this->addFieldMapping('field_ding_event_location:first_name', 'field_address:first_name');

    $this->addFieldMapping('field_ding_event_date:value', 'field_event_date');
    $this->addFieldMapping('field_ding_event_date:value2', 'field_event_date:value2');

    $this->addFieldMapping('field_ding_event_tags', 'ding_content_tags')->sourceMigration('tagsMigration');
    $this->addFieldMapping('field_ding_event_tags:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_ding_event_tags:create_term')->defaultValue(FALSE);

    $this->addFieldMapping('field_ding_event_title_image', 'field_main_image')
      ->sourceMigration('fileMigration');
    $this->addFieldMapping('field_ding_event_title_image:alt', 'field_main_image:alt');
    $this->addFieldMapping('field_ding_event_title_image:title', 'field_main_image:title');
    $this->addFieldMapping('field_ding_event_title_image:file_class')
     ->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_ding_event_list_image', 'field_list_image')
      ->sourceMigration('fileMigration');
    $this->addFieldMapping('field_ding_event_list_image:alt', 'field_list_image:alt');
    $this->addFieldMapping('field_ding_event_list_image:title', 'field_list_image:title');
    $this->addFieldMapping('field_ding_event_list_image:file_class')
     ->defaultValue('MigrateFileFid');

    $this->addFieldMapping('og_group_ref', 'og_group_ref')->sourceMigration('libraryMigration');

    $this->addFieldMapping('field_ding_event_body', 'field_ding_body');
    $this->addFieldMapping('field_ding_event_lead', 'field_ding_body:summary');
    $this->addFieldMapping('field_ding_event_body:format', 'field_ding_body:format');

    $this->addFieldMapping('field_ding_event_category', 'field_category')->sourceMigration('eventCategoryMigration');
    $this->addFieldMapping('field_ding_event_category:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_ding_event_category:create_term')->defaultValue(FALSE);

    // Migrate Editorial Dashboard statuses.
    if ($this->ed_module) {
      $this->addFieldMapping('field_editorial_status', 'edns_status')
        ->defaultValue('ed_appr');
    }

    $this->removeFieldMapping('body');
    $this->removeFieldMapping('body:language');
    $this->removeFieldMapping('body:summary');
    $this->removeFieldMapping('body:format');
  }

  protected function query() {
    $query = parent::query();
    $query->join('editorial_dashboard_node_status', 'edns', 'n.nid = edns.nid');
    $query->fields('edns', array('status'));

    return $query;
  }

  public function prepare($entity, $row) {

    if (isset($row->field_event_date[0]) && !empty($row->field_event_date[0])) {
      $entity->field_ding_event_date['und'][0]['value'] = $row->field_event_date[0];
      $entity->field_ding_event_date['und'][0]['timezone'] = "Europe/Copenhagen";
    }
    if (isset($row->{'field_event_date:value2'}[0]) && !empty($row->{'field_event_date:value2'}[0])) {
      $entity->field_ding_event_date['und'][0]['value2'] = $row->{'field_event_date:value2'}[0];
      $entity->field_ding_event_date['und'][0]['timezone'] = "Europe/Copenhagen";
    }

    $ed_nodes = variable_get('editorial_base_content_types');
    $node_ed = !empty($ed_nodes['ding_event']);
    $node_ed_status = $row->edns_status;
    $node_enabled = $entity->status == 1;

    if ($node_ed_status && $this->ed_module && $node_ed) {
      $editorial_status = (int) $entity->field_editorial_status[LANGUAGE_NONE][0]['value'];
      $ed_status_mapping = array(
        1 => 'ed_new',
        2 => 'ed_pushed',
        4 => 'ed_rej',
        8 => 'ed_appr',
      );

      if ($node_enabled) {
        $entity->field_editorial_status[LANGUAGE_NONE][0]['value'] = 'ed_appr';
      }
      else {
        $entity->field_editorial_status[LANGUAGE_NONE][0]['value'] = $ed_status_mapping[$editorial_status];
      }
    }
  }
}

/**
 * Handling specific to a Drupal 7 source for node with content type library.
 */
class EasyDDBLibraryMigration extends DrupalNode7Migration {
  /**
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBNodeMigrationGroup');

    // Dependencies.
    $this->dependencies[] ='fileMigration';
    $this->dependencies[] ='tagsMigration';

    //Mapping.
    $this->addFieldMapping('field_ding_library_addresse', 'field_address');
    $this->addFieldMapping('field_ding_library_addresse:administrative_area', 'field_address:administrative_area');
    $this->addFieldMapping('field_ding_library_addresse:sub_administrative_area', 'field_address:sub_administrative_area');
    $this->addFieldMapping('field_ding_library_addresse:locality', 'field_address:locality');
    $this->addFieldMapping('field_ding_library_addresse:dependent_locality', 'field_address:dependent_locality');
    $this->addFieldMapping('field_ding_library_addresse:postal_code', 'field_address:postal_code');
    $this->addFieldMapping('field_ding_library_addresse:thoroughfare', 'field_address:thoroughfare');
    $this->addFieldMapping('field_ding_library_addresse:premise', 'field_address:premise');
    $this->addFieldMapping('field_ding_library_addresse:sub_premise', 'field_address:sub_premise');
    $this->addFieldMapping('field_ding_library_addresse:organisation_name', 'field_address:organisation_name');
    $this->addFieldMapping('field_ding_library_addresse:name_line', 'field_address:name_line');
    $this->addFieldMapping('field_ding_library_addresse:last_name', 'field_address:last_name');
    $this->addFieldMapping('field_ding_library_addresse:data', 'field_address:data');
    $this->addFieldMapping('field_ding_library_addresse:first_name', 'field_address:first_name');

    $this->addFieldMapping('field_ding_library_slug', 'field_slug');
    $this->addFieldMapping('field_ding_library_mail', 'field_email');
    $this->addFieldMapping('field_ding_library_phone_number', 'field_phone');
    $this->addFieldMapping('field_ding_library_geocode', 'field_geocode');
    $this->addFieldMapping('field_ding_library_fax_number', 'field_fax');


    $this->addFieldMapping('field_ding_library_title_image', 'field_main_image')
      ->sourceMigration('fileMigration');
    $this->addFieldMapping('field_ding_library_title_image:alt', 'field_main_image:alt');
    $this->addFieldMapping('field_ding_library_title_image:title', 'field_main_image:title');
    $this->addFieldMapping('field_ding_library_title_image:file_class')
     ->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_ding_library_list_image', 'field_list_image')
      ->sourceMigration('fileMigration'); // @todo After implementing file migration.
    $this->addFieldMapping('field_ding_library_list_image:alt', 'field_list_image:alt');
    $this->addFieldMapping('field_ding_library_list_image:title', 'field_list_image:title');
    $this->addFieldMapping('field_ding_library_list_image:file_class')
     ->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_ding_library_links', 'field_links');
    $this->addFieldMapping('field_ding_library_links:title', 'field_links:title');
    $this->addFieldMapping('field_ding_library_links:attributes', 'field_links:attributes');

    $this->addFieldMapping('group_group', 'group_group');

    $this->addFieldMapping('field_ding_library_lead', 'field_ding_body:summary');
    $this->addFieldMapping('field_ding_library_body', 'field_ding_body');
    $this->addFieldMapping('field_ding_library_body:format', 'field_ding_body:format');

    $this->removeFieldMapping('body');
    $this->removeFieldMapping('body:language');
    $this->removeFieldMapping('body:summary');
    $this->removeFieldMapping('body:format');
  }
}

/**
 * Handling specific to a Drupal 7 source for node with content type page.
 */
class EasyDDBPageMigration extends DrupalNode7Migration {
  /**
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBNodeMigrationGroup');

    // Dependencies.
    $this->dependencies[] ='fileMigration';
    $this->dependencies[] ='tagsMigration';

    //Mapping.
    $this->addFieldMapping('field_ding_page_tags', 'ding_content_tags')->sourceMigration('tagsMigration');
    $this->addFieldMapping('field_ding_page_tags:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_ding_page_tags:create_term')->defaultValue(FALSE);

    $this->addFieldMapping('field_ding_page_materials', 'field_ding_material');

    $this->addFieldMapping('field_ding_page_list_image', 'field_page_list_image')
      ->sourceMigration('fileMigration');
    $this->addFieldMapping('field_ding_page_list_image:alt', 'field_page_list_image:alt');
    $this->addFieldMapping('field_ding_page_list_image:title', 'field_page_list_image:title');
    $this->addFieldMapping('field_ding_page_list_image:file_class')
     ->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_ding_page_lead', 'field_ding_body:summary');
    $this->addFieldMapping('field_ding_page_body', 'field_ding_body');
    $this->addFieldMapping('field_ding_page_body:format', 'field_ding_body:format');

    $this->removeFieldMapping('body');
    $this->removeFieldMapping('body:language');
    $this->removeFieldMapping('body:summary');
    $this->removeFieldMapping('body:format');
  }
}

/**
 * Handling specific to a Drupal 7 source for node with content type campaign.
 */
class EasyDDBCampaignMigration extends DrupalNode7Migration {
  /**
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBNodeMigrationGroup');

    // Dependencies.
    $this->dependencies[] ='fileMigration';
    $this->dependencies[] ='tagsMigration';
    $this->dependencies[] ='damsCategoryMigration';

    //Mapping.
    $this->addFieldMapping('field_camp_image', 'field_camp_image')
      ->sourceMigration('fileMigration');
    $this->addFieldMapping('field_camp_image:alt', 'field_camp_image:alt');
    $this->addFieldMapping('field_camp_image:title', 'field_camp_image:title');
    $this->addFieldMapping('field_camp_image:file_class')
     ->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_camp_link', 'field_camp_link');
    $this->addFieldMapping('field_camp_settings', 'field_camp_settings');
    $this->addFieldMapping('field_camp_text_full', 'field_camp_text_full');
    $this->addFieldMapping('field_camp_text_full:format', 'field_camp_text_full:format');
    $this->addFieldMapping('field_camp_text_plain', 'field_camp_text_plain');
    $this->addFieldMapping('field_camp_weight', 'field_camp_weight');


    $this->removeFieldMapping('body');
    $this->removeFieldMapping('body:language');
    $this->removeFieldMapping('body:summary');
    $this->removeFieldMapping('body:format');
  }
}
