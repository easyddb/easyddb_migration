<?php

/**
 * Defines migrating of dibs settings.
 */
class EasyDDBDibsSettingsMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBDibsMigrationGroup');

    // Set table name of source data.
    $table_name = 'dibs_order_id_settings';

    // Set machine name conform to migrate_d2d mechanism.
    $this->machineName = $arguments['machine_name'];

    // Set destination of migrating, in this case it is table.
    $this->destination = new MigrateDestinationTable($table_name);

    // Set definition of field for mapping. It should be a field which indicates each record in table.
    $this->map = new MigrateSQLMap(
      $this->machineName,
        array(
          'api_module' => array(
            'type' => 'varchar',
            'not null' => 1,
            'length' => 64,
            'alias' => 'd',
          ),
          'api_delta' => array(
            'type' => 'varchar',
            'not null' => 1,
            'length' => 64,
            'alias' => 'd',
          ),
        ),
        array(
          'api_module' => array(
            'type' => 'varchar',
            'not null' => 1,
            'length' => 64,
          ),
          'api_delta' => array(
            'type' => 'varchar',
            'not null' => 1,
            'length' => 64,
          ),
        )
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('dibs_order_id_settings', 'd')
              ->fields('d');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);

    // Set mapping for fields.
    $this->addFieldMapping('api_module', 'api_module');
    $this->addFieldMapping('api_delta', 'api_delta');
    $this->addFieldMapping('order_id', 'order_id');
    $this->addFieldMapping('order_id_prefix', 'order_id_prefix');
    $this->addFieldMapping('order_id_suffix', 'order_id_suffix');
  }
}

/**
 * Defines migrating of dibs transactions.
 */
class EasyDDBDibsTransactionsMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBDibsMigrationGroup');

    // Set table name of source data.
    $table_name = 'dibs_transactions';

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
            'alias' => 'd',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name) // Gets primary key of destination table.
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('dibs_transactions', 'd')
              ->fields('d');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);
    // Set mapping for fields.
    // $this->addFieldMapping('api_module', 'api_module')->sourceMigration('dibsSettingsMigration');
    // $this->addFieldMapping('api_delta', 'api_delta')->sourceMigration('dibsSettingsMigration');
    $this->addSimpleMappings(array(
      'api_module',
      'api_delta',
      'api_hash',
      'order_info_short',
      'order_info_long',
      'order_price_info',
      'payment_time',
      'payment_order_id',
      'payment_retry_count',
      'payment_status',
      'payment_currency',
      'payment_price',
      'payment_type',
      'payment_fee',
      'payment_transaction_type',
      'payment_transaction_id',
      'split_payments',
      'customer_uid',
      'customer_name',
      'customer_address',
      'customer_address_2',
      'customer_city',
      'customer_zipcode',
      'customer_country',
      'customer_email',
      'customer_phone',
      'params',
      'provider_payment_status',
      'dibs_capture_status',
    ));
  }
}

/**
 * Defines migrating of dibs transactions log.
 */
class EasyDDBDibsTransactionsLogMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBDibsMigrationGroup');

    // Set table name of source data.
    $table_name = 'dibs_transactions_log';

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
            'alias' => 'd',
          ),
        ),
        array(
          'tid' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
          ),
        )
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('dibs_transactions_log', 'd')
              ->fields('d');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);
    // Set mapping for fields.
    $this->addSimpleMappings(array(
      'tid',
      'type',
      'subtype',
      'log_text',
      'log_value',
      'time',
    ));
  }
}

/**
 * Defines migrating of dibs split payments.
 */
class EasyDDBDibsSplitPaymentsMigration extends Migration {

  public function __construct($arguments) {
    // Set default group.
    parent::__construct($arguments);
    $this->group = MigrateGroup::getInstance('EasyDDBDibsMigrationGroup');

    // Set table name of source data.
    $table_name = 'dibs_split_payments';

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
            'alias' => 'd',
          ),
          'payment_transaction_id' => array(
            'type' => 'int',
            'not null' => 1,
            'unsigned' => 1,
            'alias' => 'd',
          ),
        ),
        MigrateDestinationTable::getKeySchema($table_name)
      );
    // Define query for getting source data.
    $query =  Database::getConnection('default', 'migration')
              ->select('dibs_split_payments', 'd')
              ->fields('d');

    // Set query for getting source data.
    $this->sourceOptions = array('map_joinable' => FALSE, 'cache_counts' => TRUE, 'cache_key' => 'migrate_' . $this->machineName);
    $this->source = new MigrateSourceSQL($query, array(), NULL, $this->sourceOptions);
    // Set mapping for fields.
    $this->addSimpleMappings(array(
      'tid',
      'payment_transaction_id',
      'delta',
    ));
  }
}
