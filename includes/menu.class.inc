<?php
/**
 * @file
 * Implementation of menu migration.
 */

/*
 * Class for menu migration.
 */
class EasyDDBMenuMigration extends DrupalMenuMigration {
  /**
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBMenuMigrationGroup');
  }

  /**
   * Query for the basic menu data.
   *
   * @return QueryConditionInterface
   */
  protected function query() {
    $query = Database::getConnection('default', $this->sourceConnection)
             ->select('menu_custom', 'm')
             ->fields('m')
             ->condition('m.menu_name', array('user-menu', 'navigation', 'management'), 'NOT IN');
    return $query;
  }
}

/*
 * Class for menu link migration.
 */
class EasyDDBMenuLinksMigration extends DrupalMenuLinksMigration {
  /**
   * @param array $arguments
   *     $arguments['menu_migration'] should be defined -- menu links are normally
   *        dependent on menus.
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBMenuMigrationGroup');

    // Mapping.
    $this->addSimpleMappings(array('router_path', 'link_title',
        'module', 'hidden', 'external', 'has_children',
        'expanded', 'weight', 'depth', 'customized', 'p1', 'p2', 'p3', 'p4',
        'p5', 'p6', 'p7', 'p8', 'p9', 'updated'));

    if (!empty($arguments['menu_migration'])) {
      $menu_migration = $arguments['menu_migration'];
      $this->addFieldMapping('menu_name', 'menu_name')
           ->sourceMigration($menu_migration);
    }
    else {
      $this->addFieldMapping('menu_name', 'menu_name');
    }

    $this->addFieldMapping('plid', 'plid')
         ->sourceMigration($this->getMachineName());

    $this->addFieldMapping('link_path', 'link_path');
    $this->addUnmigratedSources(array('options'));
    $this->addUnmigratedDestinations(array('options'));
  }

  /**
   * Query for the basic menu_links data.
   *
   * @return QueryConditionInterface
   */
  protected function query() {
    $query = Database::getConnection('default', $this->sourceConnection)
             ->select('menu_links', 'm')
             ->fields('m')
             ->condition('m.menu_name', array('menu-footer-menu-1', 'menu-footer-menu-2', 'menu-footer-menu-3', 'menu-footer-menu-4',  'main-menu'), 'IN')
             ->condition('m.module', array('og_menu'), 'NOT IN')
             ->condition('m.link_path', db_like('node/add') . '%', 'NOT LIKE')
             ->condition('m.link_path', db_like('admin') . '%', 'NOT LIKE')
             ->condition('m.link_path', db_like('file/add') . '%', 'NOT LIKE')
             ->condition('m.mlid', 2, '>');
    return $query;
  }

  /**
   * Review a data row after fetch, returning FALSE to skip it.
   *
   * @param $row
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // NIDs first
    if (!empty($this->node_migrations)) {
      $regex_nid = "/(?<=node\/)[\d]+(?=$|\/)/";
      $regex_tid = "/(?<=taxonomy\/term\/)[\d]+(?=$|\/)/";
      $regex_file = "/(http(?:s)?:\/\/)(.*)(\/sites\/default\/.*)/";

      if (preg_match($regex_nid, $row->link_path, $matches)) {
        if ($value = $this->handleSourceMigration($this->node_migrations, $matches[0])) {
          $new_path = preg_replace('/' . $matches[0] . '/', $value, $row->link_path);
          if ($new_path) {
            $row->link_path = $new_path;
          }
          else {
          }
        }
        else {
        }
      }
      elseif (preg_match($regex_tid, $row->link_path, $matches)) {
        if ($value = $this->handleSourceMigration($this->term_migrations, $matches[0])) {
          $new_path = preg_replace('/' . $matches[0] . '/', $value, $row->link_path);
          if ($new_path) {
            $row->link_path = $new_path;
          }
          else {
          }
        }
      }
      elseif (preg_match($regex_file, $row->link_path, $matches)) {
        global $base_url;
        $domain = explode("//", $base_url);
        $new_path = preg_replace('/' . $matches[2] . '/', $domain[1], $row->link_path);
        if ($new_path) {
          $row->link_path = $new_path;
        }
        else {
        }
      }
    }
  }
}
