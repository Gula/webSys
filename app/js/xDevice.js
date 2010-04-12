
/*
 * xDevice
 *
 * @version		0.1b
 * @license		MIT-style license
 * @authors
 *  - Damian Suarez <rdsuarez@gmail.com>
 *  - Jose Mare <josmare@gmail.com>
 * @infos     http://
 * @copyright	Author
 *
 */

var xDevice = new Class({

  Version: '0.1',

  Implements: [Options, Events]

});


xDevice.Out = new Class({

  options: {
    size: {
      width: 1000,
      height: 400
    }
  },

  initialize: function(container, options) {
    this.setOptions(options);
  }

});





xDevice.Out.Grafo = new Class({

  Extends: xDevice,

  options: {

    scale: {
      x: 1,
      y: 1
    },

    xmin: 0,
    xmax: 1000,
    ymin: 0,
    ymax: 300,
    zmin: 0,
    zmax: 1,
    lineColor: '#026'
  },

  initialize: function(container, options) {
    this.setOptions(options);
    this.container = $(container);

    this.container.setStyles({
      'width': this.options.width,
      'height': this.options.height
    });

    this.canvas = new Element('canvas');
    this.canvas.adopt(new Element('div', {
      'text': 'Your browser does not support the canvas element, get a better one!',
      'styles': {
        'text-align': 'center',
        'background-color': '#8b2e19',
        'width': this.options.size.width,
        'height': this.options.size.height,
        'color': '#fff'
      }
    }));


    this.samples = [];

    this.canvas.width = this.options.size.width;
    this.canvas.height = this.options.size.height;
    this.container.adopt(this.canvas);

    if (!this.canvas.getContext) return false;
    this.ctx = this.canvas.getContext('2d');

    console.debug ("this.ctx -> ", this.ctx);

    this.ctx.lineWidth = 1;
    this.ctx.lineCap = 'round';
    this.ctx.strokeStyle = this.options.lineColor;

    this.ctx.beginPath();
    this.ctx.moveTo(0, 0);

    this.time = 0;
    this.from = [];
    this.to = [];

  },

  storeData: function(sample) {
    //this.samples.include(sample);
    
    this.from = [this.time, this.to];
    this.to = [(this.time + 1)*this.options.scale.x, sample*this.options.scale.y];

    this.time++;

    //if(this.samples.length > 40) this.samples.shift();
    this.renderPoli();
    
    //this.clear();
  },



  renderPoli: function () {
    /*
      this.ctx.lineTo(i*10, y*5);
    }, this)
    */
    this.ctx.lineTo(this.from[0], this.from[1]);
        
    this.ctx.lineTo(this.to[0], this.to[1]);
    this.ctx.stroke();

  },

  clear: function() {
    this.ctx.clearRect(0, 0, this.options.width, this.options.width);
  }
});