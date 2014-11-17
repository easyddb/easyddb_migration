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
