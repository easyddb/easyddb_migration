<?php
/**
 * @file
 * Implementation of EasyDDBFileMigration.
 */

/**
 * Handling specific to a Drupal 7 source for users.
 */
class EasyDDBFileMigration extends DrupalFile7Migration {
  /**
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('default');
  }
}
