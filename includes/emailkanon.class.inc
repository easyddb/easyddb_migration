<?php

/**
 * Defines migrating of emailkanon first_login_table.
 */
class EasyDDBEmailkanonFirstLoginMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBEmailkanonMigrationGroup');

    // Depandecies.
    $this->dependencies[] = 'userMigration';

    // Set table name of source data.
    $table_name = 'emailkanon_first_login';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'flid' => array(
          'type' => 'int',
          'not null' => 1,
          'unsigned' => 1,
          'alias' => 'e',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
    );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('emailkanon_first_login', 'e')
              ->fields('e');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('uid', 'uid')->sourceMigration('userMigration');
  }
}

/**
 * Defines migrating of emailkanon users.
 */
class EasyDDBEmailkanonUsersMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBEmailkanonMigrationGroup');

    // Set table name of source data.
    $table_name = 'emailkanon_users';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'email' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
    );

    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('emailkanon_users', 'e')
              ->fields('e');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('email', 'email');
    $this->addFieldMapping('subscription', 'subscription');
  }
}

/**
 * Defines migrating of emailkanon queue.
 */
class EasyDDBEmailkanonQueueMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBEmailkanonMigrationGroup');

    // Dependencies.
    $this->dependencies[] = 'newslettersMigration';
    $this->dependencies[] = 'mailinglistMigration';
    $this->dependencies[] = 'userMigration';

    // Set table name of source data.
    $table_name = 'emailkanon_queue';

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
          'alias' => 'e',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
    );

    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('emailkanon_queue', 'e')
              ->fields('e');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('entityId', 'entityId');
    $this->addFieldMapping('method', 'method');
    $this->addFieldMapping('arguments', 'arguments');
    $this->addFieldMapping('response', 'response');
    $this->addFieldMapping('created', 'created');
    $this->addFieldMapping('processed', 'processed');
    $this->addFieldMapping('status', 'status');
  }

  public function prepare($e, $r) {
    if (in_array($r->method, array('createNewsletter', 'getNewsletter', 'testNewsletter', 'configureNewsletter', 'sendNewsletter', 'getNewsletterDetails'))) {
      // Array of all related migration.
      $sources = array(
        'newslettersMigration',
      );
      $e->entityId = NULL;
      foreach ($sources as $source) {
        $source_migration = Migration::getInstance($source);
        $source_migration->sourceKeyMap['nid'] = 'nid';
        $destid = $source_migration->getMap()->lookupDestinationID(array($r->entityId));
        if (!empty($destid)) {
          $e->entityId = current($destid);
        }
      }
    }
    else if (in_array($r->method, array('createMailingList', 'addMailinglistsToUserGroup'))) {
      // Array of all related migration.
      $sources = array(
        'mailinglistMigration',
      );
      $e->entityId = NULL;
      foreach ($sources as $source) {
        $source_migration = Migration::getInstance($source);
        $source_migration->sourceKeyMap['tid'] = 'tid';
        $destid = $source_migration->getMap()->lookupDestinationID(array($r->entityId));
        if (!empty($destid)) {
          $e->entityId = current($destid);
        }
      }
    }
    else if (in_array($r->method, array('subscribe', 'unsubscribe'))) {
      // Array of all related migration.
      $sources = array(
       'userMigration',
      );
      $e->entityId = NULL;
      foreach ($sources as $source) {
        $source_migration = Migration::getInstance($source);
        $source_migration->sourceKeyMap['uid'] = 'uid';
        $destid = $source_migration->getMap()->lookupDestinationID(array($r->entityId));
        if (!empty($destid)) {
          $e->entityId = current($destid);
        }
      }
    }
  }
}

/**
 * Defines migrating of emailkanon newsletters.
 */
class EasyDDBEmailkanonNewslettersMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBEmailkanonMigrationGroup');

    // Dependencies.
    $this->dependencies[] = 'newslettersMigration';

    // Set table name of source data.
    $table_name = 'emailkanon_newsletters';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

     // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'nid' => array(
          'type' => 'int',
          'not null' => 1,
          'unsigned' => 1,
          'alias' => 'e',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
    );

    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('emailkanon_newsletters', 'e')
              ->fields('e');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('nid', 'nid')->sourceMigration('newslettersMigration');
    $this->addFieldMapping('newsletter_id', 'newsletter_id');
    $this->addFieldMapping('state', 'state');
  }
}

/**
 * Defines migrating of emailkanon mailinglists.
 */
class EasyDDBEmailkanonMailinglistsMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBEmailkanonMigrationGroup');

    // Dependencies.
    $this->dependencies[] = 'mailinglistMigration';

    // Set table name of source data.
    // Set table name of source data.
    $table_name = 'emailkanon_mailinglists';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

     // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
      array(
        'tid' => array(
          'type' => 'int',
          'not null' => 1,
          'unsigned' => 1,
          'alias' => 'e',
        ),
      ),
      MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
    );

    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('emailkanon_mailinglists', 'e')
              ->fields('e');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('tid', 'tid')->sourceMigration('mailinglistMigration');
    $this->addFieldMapping('mailinglist_id', 'mailinglist_id');
    $this->addFieldMapping('state', 'state');
    $this->addFieldMapping('access_rules', 'access_rules');
  }
}
