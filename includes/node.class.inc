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
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBNodeMigrationGroup');

    //Mapping.
    $this->addFieldMapping('field_ding_news_category', 'field_category')->sourceMigration('categoryMigration');
    $this->addFieldMapping('field_ding_news_category:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_ding_news_category:create_term')->defaultValue(FALSE);

    // $this->addFieldMapping('ding_news_groups_ref', 'group_audience');

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

    $this->addFieldMapping('field_ding_news_title_image', 'field_main_image')
      ->sourceMigration('fileMigration');
    $this->addFieldMapping('field_ding_news_title_image:file_class')
      ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_ding_news_title_image:alt', 'field_main_image:alt');
    $this->addFieldMapping('field_ding_news_title_image:title', 'field_main_image:title');

    $this->removeFieldMapping('body');
    $this->removeFieldMapping('body:language');
    $this->removeFieldMapping('body:summary');
    $this->removeFieldMapping('body:format');
  }
}

/**
 * Handling specific to a Drupal 7 source for node with content type events.
 */
class EasyDDBEventsMigration extends DrupalNode7Migration {
  /**
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBNodeMigrationGroup');

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

    // $this->addFieldMapping('og_group_ref', 'field_audience');
    // $this->addFieldMapping('ding_event_groups_ref', 'og_group_ref');

    $this->addFieldMapping('field_ding_event_body', 'field_ding_body');
    $this->addFieldMapping('field_ding_event_lead', 'field_ding_body:summary');
    $this->addFieldMapping('field_ding_event_body:format', 'field_ding_body:format');

    $this->addFieldMapping('field_ding_event_category', 'field_category')->sourceMigration('categoryMigration');
    $this->addFieldMapping('field_ding_event_category:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_ding_event_category:create_term')->defaultValue(FALSE);

    $this->removeFieldMapping('body');
    $this->removeFieldMapping('body:language');
    $this->removeFieldMapping('body:summary');
    $this->removeFieldMapping('body:format');
  }

  public function prepare($e, $r) {
    if (isset($r->field_event_date[0]) && !empty($r->field_event_date[0])) {
      $e->field_ding_event_date['und'][0]['value'] = $r->field_event_date[0];
    }
    if (isset($r->{'field_event_date:value2'}[0]) && !empty($r->{'field_event_date:value2'}[0])) {
      $e->field_ding_event_date['und'][0]['value2'] = $r->{'field_event_date:value2'}[0];
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
    // $this->addFieldMapping('ding_event_groups_ref', 'og_group_ref');

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
