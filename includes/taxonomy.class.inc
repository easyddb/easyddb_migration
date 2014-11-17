<?php

class EasyDDBCategoryMigration extends DrupalTerm7Migration {
  /**
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBTaxonomyMigrationGroup');
  }
}

class EasyDDBTagsMigration extends DrupalTerm7Migration {
  /**
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBTaxonomyMigrationGroup');
  }
}
