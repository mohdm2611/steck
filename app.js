var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const mongoose = require('mongoose');

var indexRouter = require('./api/routes/index');
var modulesRouter = require('./api/routes/modules');
var usersRouter = require('./api/routes/users');
var hbs = require('express-handlebars');
var expressValidator = require('express-validator');
var session = require('express-session');
var flash = require('express-flash');

var app = express();

mongoose.connect('mongodb://admin:'+ 
  process.env.MONGO_ATLAS_PW + '@steck-shard-00-00-j16h3.mongodb.net:27017,steck-shard-00-01-j16h3.mongodb.net:27017,steck-shard-00-02-j16h3.mongodb.net:27017/test?ssl=true&replicaSet=Steck-shard-0&authSource=admin&retryWrites=true'
  ,{ useNewUrlParser: true });
// view engine setup
mongoose.Promise = global.Promise;
app.engine('hbs',hbs({extname: 'hbs', defaultLayout: 'layout', layoutsDir: __dirname + '/views/layouts'}));
app.set('views', path.join(__dirname, '/views/layouts'));
app.set('view engine', 'hbs');


app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(expressValidator());  
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use(session({
  secret: 'dasfdsgaersd',
  resave: false,
  saveUninitialized: true
}))
app.use(flash());

app.use(function(req, res, next) {
  res.header('Access-Control-Allow-Origin', '*');
  res.header('Access-Control-Allow-Headers', 'Origin, X-Requested-With, Content-Type, Accept, Authorization');
  if(req.method === 'OPTIONS') {
    res.header('Access-Control-Allow-Methods', 'PUT, POST, GET, PATCH, DELETE,');
    return res.status(200).json({});
  }
  next();
});
app.use('/', indexRouter);
app.use('/modules', modulesRouter);
app.use('/users', usersRouter);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
  res.set('Cache-Control', 'no-cache, private, no-store, must-revalidate, max-stale=0, post-check=0, pre-check=0');
});

module.exports = app;
