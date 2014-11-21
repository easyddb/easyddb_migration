<?php

/**
 * Defines migrating of .
 */
class EasyDDBOgMembershipTypeMigration extends DynamicMigration {

  public function __construct($arguments) {
    // Set default group.
    $group = MigrateGroup::getInstance('EasyDDBOgMigrationGroup');
    parent::__construct($group);


    // Set table name of source data.
    $table_name = 'og_membership_type';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'id' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'o',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('og_membership_type', 'o')
              ->fields('o', array('id', 'name', 'description', 'status', 'module', 'language'));

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('name', 'name')
      ->dedupe('og_membership_type', 'name');
    $this->addFieldMapping('description', 'description');
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('module', 'module');
    $this->addFieldMapping('language', 'language');
  }
}

/**
 * Defines migrating of .
 */
class EasyDDBOgMembershipMigration extends DynamicMigration {

  public function __construct($arguments) {
    // Set default group.
    $group = MigrateGroup::getInstance('EasyDDBOgMigrationGroup');
    parent::__construct($group);

    // Dependencies.
    $this->dependencies[] ='ogMembershipTypeMigration';
    $this->dependencies[] ='newsMigration';
    $this->dependencies[] ='eventsMigration';
    $this->dependencies[] ='libraryMigration';
    $this->dependencies[] ='pageMigration';
    $this->dependencies[] ='campaignMigration';

    // Set table name of source data.
    $table_name = 'og_membership';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'id' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'o',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('og_membership', 'o')
              ->fields('o', array('id', 'type', 'etid', 'entity_type', 'gid', 'group_type', 'state', 'created', 'field_name', 'language'));

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('type', 'type');
    $this->addFieldMapping('etid', 'etid');
    $this->addFieldMapping('entity_type', 'entity_type');
    $this->addFieldMapping('gid', 'gid')->sourceMigration('libraryMigration');
    $this->addFieldMapping('group_type', 'group_type');
    $this->addFieldMapping('state', 'state');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('field_name', 'field_name');
    $this->addFieldMapping('language', 'language');
  }

  public function prepare($e, $r) {
    // Array of all related migration.
    $sources = array(
      'user' => array(
        'userMigration'
      ),
      'node' => array(
        'newsMigration',
        'eventsMigration',
        'libraryMigration',
        'pageMigration',
        'campaignMigration',
      ),
    );
    $e->etid = NULL;
    foreach ($sources[$r->entity_type] as $sources) {
      $source_migration = Migration::getInstance($sources);
      $source_migration->sourceKeyMap['nid'] = 'nid';
      $destid = $source_migration->getMap()->lookupDestinationID(array($r->etid));
      if (!empty($destid)) {
        $e->etid = current($destid);
      }
    }
  }
}


/**
 * Defines migrating of .
 */
class EasyDDBOgMenuMigration extends DynamicMigration {

  public function __construct($arguments) {
    // Set default group.
    $group = MigrateGroup::getInstance('EasyDDBOgMigrationGroup');
    parent::__construct($group);


    // Set table name of source data.
    $table_name = 'og_menu';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
       array(
          'menu_name' => array(
            'type' => 'varchar',
            'length' => 32,
            'default' => '',
            'not null' => 1,
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('og_menu', 'o')
              ->fields('o', array('menu_name', 'gid', 'group_type'));

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('gid', 'gid');
    $this->addFieldMapping('group_type', 'group_type');
  }
}

/**
 * Defines migrating of .
 */
class EasyDDBOgRoleMigration extends DynamicMigration {

  public function __construct($arguments) {
    // Set default group.
    $group = MigrateGroup::getInstance('EasyDDBOgMigrationGroup');
    parent::__construct($group);


    // Set table name of source data.
    $table_name = 'og_role';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
       array(
          'rid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'o',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('og_role', 'o')
              ->fields('o', array('rid', 'gid', 'group_type', 'name', 'group_bundle'));

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('gid', 'gid');
    $this->addFieldMapping('group_type', 'group_type');
    $this->addFieldMapping('group_bundle', 'group_bundle');
    $this->addFieldMapping('name', 'name');
  }
}

/**
 * Defines migrating of .
 */
class EasyDDBOgRolePermissionMigration extends DynamicMigration {

  public function __construct($arguments) {
    // Set default group.
    $group = MigrateGroup::getInstance('EasyDDBOgMigrationGroup');
    parent::__construct($group);


    // Set table name of source data.
    $table_name = 'og_role_permission';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
       array(
          'rid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'o',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('og_role_permission', 'o')
              ->fields('o', array('rid', 'permission', 'module'));

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('rid', 'rid')
      ->sourceMigration('ogRoleMigration');
    $this->addFieldMapping('permission', 'permission');
    $this->addFieldMapping('module', 'module');
  }
}

/**
 * Defines migrating of .
 */
class EasyDDBOgUsersRolesMigration extends DynamicMigration {

  public function __construct($arguments) {
    // Set default group.
    $group = MigrateGroup::getInstance('EasyDDBOgMigrationGroup');
    parent::__construct($group);


    // Set table name of source data.
    $table_name = 'og_users_roles';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
       array(
          'uid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'o',
          ),
           'rid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'o',
          ),
            'gid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'o',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('og_users_roles', 'o')
              ->fields('o', array('uid', 'rid', 'gid', 'group_type'));

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('rid', 'rid')
      ->sourceMigration('ogRoleMigration');
    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('userMigration');
    $this->addFieldMapping('gid', 'gid');
    $this->addFieldMapping('group_type', 'group_type');
  }
}