class Sjson
	# Encodes the Hash o in the simplified SJSON format and returns it.
	# The Hash can contain bools, numbers, strings, Arrays and Hashes.
	def self.encode(o)
		SjsonWriter.new().write_root_object(o)
	end

	def self.save(o, path)
		File.open(path, "w") do |file|
			file.puts(encode(o))
		end
	end

	# Decodes the SJSON string s into a Hash
	def self.decode(s)
		SjsonReader.new(s).parse_root_object()
	end

	def self.load(path)
		begin
			return decode(IO.read(path))
		rescue RuntimeError => e
			raise "#{e.message} in `#{path}`"
		end
	end
end

class SjsonWriter
	def initialize
		@s = ''
		@indent = 0
	end

	def write_root_object(o)
		write_object_fields(o)
		return @s
	end

	def write_object_fields(o)
		o.keys.sort.each do |key|
			write_new_line()
			write_key(key)
			@s << ' = '
			write(o[key])
		end
	end

	def write_new_line()
		@s << "\n" << "\t" * @indent
	end

	def write_key(key)
		if key[/^[a-zA-Z0-9_]*$/]
			@s << key
		else
			write_string(key)
		end
	end

	def write(o)
		if o == nil
			@s << 'null'
		elsif o == false
			@s << 'false'
		elsif o == true
			@s << 'true'
		elsif o.is_a?(Numeric)
			@s << o.to_s
		elsif o.is_a?(String)
			write_string(o)
		elsif o.is_a?(Array)
			write_array(o)
		elsif o.is_a?(Hash)
			write_object(o)
		else
			@s << '### error'
		end
	end

	def write_string(s)
		@s << '"' << s.gsub('\\') {'\\\\'}.gsub('"', '\\"') << '"'
	end

	def write_array(a)
		@s << '['
		@indent += 1
		a.each do |it|
			@s << ' '
			write(it)
		end
		@indent -= 1
		@s << ']'
	end

	def write_object(o)
		@s << '{'
		@indent += 1
		write_object_fields(o)
		@indent -= 1
		write_new_line()
		@s << '}'
	end
end

class SjsonReader
	def initialize(s)
		@s = s
		@i = 0
		@start_i = @i
	end

	def parse_root_object()
		ht = {}
		while (!at_end) do
			key = parse_identifier()
			consume('=')
			ht[key] = parse_value()
		end
		return ht
	end

	def at_end()
		skip_whitespace()
		return @i >= @s.length
	end

	def skip_whitespace()
		while (@i < @s.length)
			c = @s[@i,1]
			if c == "/"
				skip_comment()
			elsif c == ' ' || c == "\t" || c == "\n" || c == "\r" || c == ","
				@i+=1
			else
				break
			end
		end
	end

	def skip_comment()
		n = @s[@i+1,1]
		if n == "/"
			while @i + 1 < @s.length && @s[@i,1] != "\n"
				@i+=1
			end
			@i+=1
		elsif n == "*"
			while @i + 2 < @s.length && (@s[@i,1] != "*" || @s[@i+1,1] != "/")
				@i+=1
			end
			@i+=2
		else
			error 'bad format'
		end
	end

	def parse_identifier()
		skip_whitespace()
		return parse_string() if @s[@i,1] == '"'

		s = ""
		while true
			c = @s[@i,1]
			break if c == " " || c == "\t" || c == "\n" || c == "="
			s << c
			@i += 1
		end
		return s
	end

	def consume(s)
		skip_whitespace()
		s.each_byte do |c|
			error "bad format consuming #{s}" unless @s[@i,1] == c.chr
			@i += 1
		end
	end

	def parse_value()
		@start_i = @i
		case next_char()
		when "{" then return parse_object()
		when "[" then return parse_array()
		when "\"" then return parse_string()
		when "-", "0".."9" then return parse_number()
		when "t" then consume("true"); return true
		when "f" then consume("false"); return false
		when "n" then consume("null"); return nil
		else
			error 'bad format'
		end
	end

	def next_char
		skip_whitespace()
		return @s[@i,1]
	end

	def parse_object()
		ht = {}
		consume('{')
		while next_char != "}"
			key = parse_identifier
			consume('=')
			ht[key] = parse_value
		end
		consume('}')
		return ht
	end

	def parse_array()
		a = []
		consume('[')
		a << parse_value while next_char != "]"
		consume(']')
		return a
	end

	def parse_string()
		s = ""
		consume('"')
		while true
			c = @s[@i,1]
			@i += 1
			case c
			when "\"" then break
			when "\\"
				q = @s[@i,1]
				@i += 1
				case q
				when "\"", "\\", "/" then s << q
				when "b" then s << "\b"
				when "f" then s << "\f"
				when "n" then s << "\n"
				when "r" then s << "\r"
				when "t" then s << "\t"
				else error 'bad format'
				end
			when nil then error 'end of file while parsing string'
			else s << c
			end
		end
		return s
	end

	def parse_number()
		e = @i
		is_float = false
		while e < @s.length && "0123456789+-.eE".include?(@s[e])
			is_float = is_float || ".eE".include?(@s[e])
			e += 1
		end
		if is_float then
			num = @s[@i, e-@i].to_f
		else
			num = @s[@i, e-@i].to_i
		end
		@i = e
		return num
	end

	def error(s)
		start_line = @s[1,@start_i].lines.size
		line = @s[1,@i].lines.size
		raise "Sjson error in line(s) #{start_line}--#{line}: #{s}\nNear `#{@s[@i,50]}`"
	end
end
